add_member_after(struct member *mem, struct category *cat, struct member *place)
{
	struct member *tmp;

	AST_LIST_TRAVERSE(&cat->members, tmp, list) {
		if (!strcmp(tmp->name, mem->name)) {
			fprintf(stderr, "Member '%s' already exists in category '%s', ignoring.\n", mem->name, cat->name);
			return -1;
		}
	}
	AST_LIST_INSERT_AFTER(&cat->members, place, mem, list);

	return 0;

}
