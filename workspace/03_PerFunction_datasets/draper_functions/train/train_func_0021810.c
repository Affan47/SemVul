process_defaults(void)
{
	struct category *cat;
	struct member *mem;

	print_debug("Processing default values since config was not present\n");

	AST_LIST_TRAVERSE(&categories, cat, list) {
		AST_LIST_TRAVERSE(&cat->members, mem, list) {
			if (mem->is_separator) {
				continue;
			}

			if (!mem->defaultenabled)
				continue;

			if (mem->depsfailed == HARD_FAILURE)
				continue;

			if (mem->conflictsfailed == HARD_FAILURE)
				continue;

			if (!strcasecmp(mem->defaultenabled, "yes")) {
				mem->enabled = 1;
				mem->was_defaulted = 1;
			} else if (!strcasecmp(mem->defaultenabled, "no")) {
				mem->enabled = 0;
				mem->was_defaulted = 1;
			} else
				fprintf(stderr, "Invalid defaultenabled value for '%s' in category '%s'\n", mem->name, cat->name);
		}
	}

}
