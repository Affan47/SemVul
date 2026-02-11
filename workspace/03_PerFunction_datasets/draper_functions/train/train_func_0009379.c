xtables_find_match(const char *name, enum xtables_tryload tryload,
		   struct xtables_rule_match **matches)
{
	struct xtables_match **dptr;
	struct xtables_match *ptr;
	const char *icmp6 = "icmp6";

	if (strlen(name) >= XT_EXTENSION_MAXNAMELEN)
		xtables_error(PARAMETER_PROBLEM,
			   "Invalid match name \"%s\" (%u chars max)",
			   name, XT_EXTENSION_MAXNAMELEN - 1);


	if ( (strcmp(name,"icmpv6") == 0) ||
	     (strcmp(name,"ipv6-icmp") == 0) ||
	     (strcmp(name,"icmp6") == 0) )
		name = icmp6;


	for (dptr = &xtables_pending_matches; *dptr; ) {
		if (strcmp(name, (*dptr)->name) == 0) {
			ptr = *dptr;
			*dptr = (*dptr)->next;
			ptr->next = NULL;
			xtables_fully_register_pending_match(ptr);
		} else {
			dptr = &((*dptr)->next);
		}
	}

	for (ptr = xtables_matches; ptr; ptr = ptr->next) {
		if (strcmp(name, ptr->name) == 0) {
			struct xtables_match *clone;


			if (ptr->m == NULL)
				break;


			clone = xtables_malloc(sizeof(struct xtables_match));
			memcpy(clone, ptr, sizeof(struct xtables_match));
			clone->mflags = 0;

			clone->next = clone;

			ptr = clone;
			break;
		}
	}

#ifndef NO_SHARED_LIBS
	if (!ptr && tryload != XTF_DONT_LOAD && tryload != XTF_DURING_LOAD) {
		ptr = load_extension(xtables_libdir, afinfo->libprefix,
		      name, false);

		if (ptr == NULL && tryload == XTF_LOAD_MUST_SUCCEED)
			xt_params->exit_err(PARAMETER_PROBLEM,
				   "Couldn't load match `%s':%s\n",
				   name, strerror(errno));
	}
#else
	if (ptr && !ptr->loaded) {
		if (tryload != XTF_DONT_LOAD)
			ptr->loaded = 1;
		else
			ptr = NULL;
	}
	if(!ptr && (tryload == XTF_LOAD_MUST_SUCCEED)) {
		xt_params->exit_err(PARAMETER_PROBLEM,
			   "Couldn't find match `%s'\n", name);
	}
#endif

	if (ptr && matches) {
		struct xtables_rule_match **i;
		struct xtables_rule_match *newentry;

		newentry = xtables_malloc(sizeof(struct xtables_rule_match));

		for (i = matches; *i; i = &(*i)->next) {
			if (strcmp(name, (*i)->match->name) == 0)
				(*i)->completed = true;
		}
		newentry->match = ptr;
		newentry->completed = false;
		newentry->next = NULL;
		*i = newentry;
	}

	return ptr;
}
