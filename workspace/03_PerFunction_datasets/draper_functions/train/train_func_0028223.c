clear_enabled(struct category *cat, int index)
{
	struct member *mem;
	int i = 0;

	AST_LIST_TRAVERSE(&cat->members, mem, list) {
		if (mem->is_separator) {
			continue;
		}

		if (i++ == index)
			break;
	}

	if (!mem)
		return;

	clear_member_enabled(mem);
}
