peel_onion(const char *name, int len, unsigned char *sha1)
{
	unsigned char outer[20];
	const char *sp;
	unsigned int expected_type = 0;
	struct object *o;


	if (len < 4 || name[len-1] != '}')
		return -1;

	for (sp = name + len - 1; name <= sp; sp--) {
		int ch = *sp;
		if (ch == '{' && name < sp && sp[-1] == '^')
			break;
	}
	if (sp <= name)
		return -1;

	sp++;
	if (!strncmp(commit_type, sp, 6) && sp[6] == '}')
		expected_type = OBJ_COMMIT;
	else if (!strncmp(tree_type, sp, 4) && sp[4] == '}')
		expected_type = OBJ_TREE;
	else if (!strncmp(blob_type, sp, 4) && sp[4] == '}')
		expected_type = OBJ_BLOB;
	else if (sp[0] == '}')
		expected_type = OBJ_NONE;
	else if (sp[0] == '/')
		expected_type = OBJ_COMMIT;
	else
		return -1;

	if (get_sha1_1(name, sp - name - 2, outer))
		return -1;

	o = parse_object(outer);
	if (!o)
		return -1;
	if (!expected_type) {
		o = deref_tag(o, name, sp - name - 2);
		if (!o || (!o->parsed && !parse_object(o->sha1)))
			return -1;
		hashcpy(sha1, o->sha1);
		return 0;
	}


	o = peel_to_type(name, len, o, expected_type);
	if (!o)
		return -1;

	hashcpy(sha1, o->sha1);
	if (sp[0] == '/') {

		char *prefix;
		int ret;
		struct commit_list *list = NULL;


		if (sp[1] == '}')
			return 0;

		prefix = xstrndup(sp + 1, name + len - 1 - (sp + 1));
		commit_list_insert((struct commit *)o, &list);
		ret = get_sha1_oneline(prefix, sha1, list);
		free(prefix);
		return ret;
	}
	return 0;
}
