check_prereqs(void *data, void *state)
{
	encap_profile_t *epp;
	profile_prereq_t *ppp;
	profile_environment_t *pep;
	char buf[MAXPATHLEN], pkgdir[MAXPATHLEN];
	struct stat s;

	ppp = (profile_prereq_t *)data;
	epp = (encap_profile_t *)state;

	snprintf(pkgdir, sizeof(buf), "%s/%s", source, ppp->pp_pkgspec);
	if (stat(pkgdir, &s) == -1)
	{
		if (errno == ENOENT)
		{
			fprintf(stderr, "mkencap: build-time "
				"prerequisite %s not found\n", pkgdir);
			return -1;
		}
		fprintf(stderr, "mkencap: stat(\"%s\"): %s\n",
			pkgdir, strerror(errno));
		return -1;
	}
	if (!S_ISDIR(s.st_mode))
	{
		fprintf(stderr, "mkencap: build-time prerequisite "
			"%s not found\n", pkgdir);
		return -1;
	}


	if (ppp->pp_use_bin == 1)
	{
		pep = (profile_environment_t *)calloc(1, sizeof(profile_environment_t));

		pep->pe_type = PROF_TYPE_PREPEND;
		pep->pe_variable = strdup("PATH");
		snprintf(buf, sizeof(buf), "%s/bin:", pkgdir);
		pep->pe_value = strdup(buf);

		if (epp->ep_env_vars_l == NULL)
			epp->ep_env_vars_l = encap_list_new(LIST_QUEUE, NULL);

		encap_list_add(epp->ep_env_vars_l, pep);
	}
	if (ppp->pp_use_lib == 1)
	{
		if (epp->ep_env_vars_l == NULL)
			epp->ep_env_vars_l = encap_list_new(LIST_QUEUE, NULL);

		pep = (profile_environment_t *)calloc(1, sizeof(profile_environment_t));

		pep->pe_type = PROF_TYPE_APPEND;
		pep->pe_variable = strdup("CPPFLAGS");
		snprintf(buf, sizeof(buf), " -I%s/include", pkgdir);
		pep->pe_value = strdup(buf);

		encap_list_add(epp->ep_env_vars_l, pep);

		pep = (profile_environment_t *)calloc(1, sizeof(profile_environment_t));

		pep->pe_type = PROF_TYPE_APPEND;
		pep->pe_variable = strdup("LDFLAGS");
		snprintf(buf, sizeof(buf), " -L%s/lib", pkgdir);
		pep->pe_value = strdup(buf);

		encap_list_add(epp->ep_env_vars_l, pep);
	}

	return 0;
}
