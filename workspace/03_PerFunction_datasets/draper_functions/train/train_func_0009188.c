get_shallow_commits(struct object_array *heads, int depth,
		int shallow_flag, int not_shallow_flag)
{
	int i = 0, cur_depth = 0;
	struct commit_list *result = NULL;
	struct object_array stack = {0, 0, NULL};
	struct commit *commit = NULL;

	while (commit || i < heads->nr || stack.nr) {
		struct commit_list *p;
		if (!commit) {
			if (i < heads->nr) {
				commit = (struct commit *)
					deref_tag(heads->objects[i++].item, NULL, 0);
				if (commit->object.type != OBJ_COMMIT) {
					commit = NULL;
					continue;
				}
				if (!commit->util)
					commit->util = xmalloc(sizeof(int));
				*(int *)commit->util = 0;
				cur_depth = 0;
			} else {
				commit = (struct commit *)
					stack.objects[--stack.nr].item;
				cur_depth = *(int *)commit->util;
			}
		}
		parse_commit(commit);
		commit->object.flags |= not_shallow_flag;
		cur_depth++;
		for (p = commit->parents, commit = NULL; p; p = p->next) {
			if (!p->item->util) {
				int *pointer = xmalloc(sizeof(int));
				p->item->util = pointer;
				*pointer =  cur_depth;
			} else {
				int *pointer = p->item->util;
				if (cur_depth >= *pointer)
					continue;
				*pointer = cur_depth;
			}
			if (cur_depth < depth) {
				if (p->next)
					add_object_array(&p->item->object,
							NULL, &stack);
				else {
					commit = p->item;
					cur_depth = *(int *)commit->util;
				}
			} else {
				commit_list_insert(p->item, &result);
				p->item->object.flags |= shallow_flag;
			}
		}
	}

	return result;
}
