source_attr_handler(profile_state_t *psp, const char **attr)
{
	int i;
	profile_source_t *psrcp;

#ifdef DEBUG
	printf("==> source_attr_handler()\n");
#endif

	psrcp = (profile_source_t *)calloc(1, sizeof(profile_source_t));
	psrcp->ps_use_objdir = -1;
	psrcp->ps_create_subdir = -1;
	psrcp->ps_configure_cmds = strdup(DEFAULT_CONFIGURE_CMDS);
	psrcp->ps_build_cmds = strdup(DEFAULT_BUILD_CMDS);
	psrcp->ps_install_cmds = strdup(DEFAULT_INSTALL_CMDS);
	psrcp->ps_clean_cmds = strdup(DEFAULT_CLEAN_CMDS);
	psrcp->ps_url_l = encap_list_new(LIST_QUEUE, NULL);

	for (i = 0; attr[i] != NULL; i += 2)
	{
		if (strcmp(attr[i], "url") == 0)
		{
			encap_list_add_str(psrcp->ps_url_l,
					   (char *)attr[i + 1],
					   " \t\n");
			continue;
		}

		if (strcmp(attr[i], "use_objdir") == 0)
		{
			psrcp->ps_use_objdir = parse_boolean((char *)attr[i + 1]);
			continue;
		}

		if (strcmp(attr[i], "subdir") == 0)
		{
			strlcpy(psrcp->ps_subdir, (char *)attr[i + 1],
				sizeof(psrcp->ps_subdir));
			continue;
		}

		if (strcmp(attr[i], "build_subdir") == 0)
		{
			strlcpy(psrcp->ps_build_subdir, (char *)attr[i + 1],
				sizeof(psrcp->ps_build_subdir));
			continue;
		}

		if (strcmp(attr[i], "create_subdir") == 0)
		{
			psrcp->ps_create_subdir = parse_boolean((char *)attr[i + 1]);
			continue;
		}

#if 0
		if (strcmp(attr[i], "use_DESTDIR") == 0)
		{
			psrcp->ps_use_DESTDIR = parse_boolean((char *)attr[i + 1]);
			continue;
		}
#endif

		parse_error(psp->ps_parser,
			    "<source> element: unknown attribute \"%s\"",
			    attr[i]);

	}

	if (encap_list_nents(psrcp->ps_url_l) == 0)
	{
		parse_error(psp->ps_parser,
			    "<source> element: missing url attribute");

	}

	if (psp->ps_profile->ep_sources_l == NULL)
		psp->ps_profile->ep_sources_l = encap_list_new(LIST_QUEUE,
							       NULL);

	encap_list_add(psp->ps_profile->ep_sources_l, psrcp);
	psp->ps_el_data[psp->ps_depth] = psrcp;
}
