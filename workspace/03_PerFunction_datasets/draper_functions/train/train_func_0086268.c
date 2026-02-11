netsnmp_clear_user_domain(void)
{
    struct netsnmp_lookup_domain *run = domains, *prev = NULL;

    while (run) {
	if (run->userDomain != NULL) {
            destroy_word_array(run->userDomain);
	    run->userDomain = NULL;
	}
	if (run->domain == NULL) {
	    struct netsnmp_lookup_domain *tmp = run;
	    if (prev)
		run = prev->next = run->next;
	    else
		run = domains = run->next;
	    free(tmp->application);
	    free(tmp);
	} else {
	    prev = run;
	    run = run->next;
	}
    }
}
