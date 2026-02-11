environment_attr_handler(profile_state_t *psp, const char **attr)
{
	int i;
	profile_environment_t *pep;

#ifdef DEBUG
	printf("==> environment_attr_handler()\n");
#endif

	pep = (profile_environment_t *)calloc(1, sizeof(profile_environment_t));
	pep->pe_type = -1;

	for (i = 0; attr[i] != NULL; i += 2)
	{
		if (strcmp(attr[i], "type") == 0)
		{
			pep->pe_type = parse_type((char *)attr[i + 1]);
			continue;
		}

		if (strcmp(attr[i], "variable") == 0)
		{
			pep->pe_variable = strdup((char *)attr[i + 1]);
			continue;
		}

		if (strcmp(attr[i], "value") == 0)
		{
			pep->pe_value = strdup((char *)attr[i + 1]);
			continue;
		}

		parse_error(psp->ps_parser,
			    "<environment> element: unknown attribute \"%s\"",
			    attr[i]);

	}

	if (pep->pe_variable == NULL)
	{
		parse_error(psp->ps_parser, "<environment> element: "
			    "missing variable attribute");

	}

	if (psp->ps_profile->ep_env_vars_l == NULL)
		psp->ps_profile->ep_env_vars_l = encap_list_new(LIST_QUEUE,
								NULL);

	encap_list_add(psp->ps_profile->ep_env_vars_l, pep);
	psp->ps_el_data[psp->ps_depth] = pep;
}
