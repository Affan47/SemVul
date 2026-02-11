find_match(const char *name, enum arpt_tryload tryload)
{
	struct arptables_match *ptr;

	for (ptr = arptables_matches; ptr; ptr = ptr->next) {
		if (strcmp(name, ptr->name) == 0)
			break;
	}

	if (ptr && !ptr->loaded) {
		if (tryload != DONT_LOAD)
			ptr->loaded = 1;
		else
			ptr = NULL;
	}
	if(!ptr && (tryload == LOAD_MUST_SUCCEED)) {
		exit_error(PARAMETER_PROBLEM,
			   "Couldn't find match `%s'\n", name);
	}

	if (ptr)
		ptr->used = 1;

	return ptr;
}
