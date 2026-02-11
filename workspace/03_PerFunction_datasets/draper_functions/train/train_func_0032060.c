patch_attr_handler(profile_state_t *psp, const char **attr)
{
	int i;
	profile_patch_t *ppp;
	profile_source_t *psrcp;
	encap_list_t **pclp;

#ifdef DEBUG
	printf("==> patch_attr_handler()\n");
#endif

	ppp = (profile_patch_t *)calloc(1, sizeof(profile_patch_t));
	ppp->pp_fd = -1;

	for (i = 0; attr[i] != NULL; i += 2)
	{
		if (strcmp(attr[i], "url") == 0)
		{
			ppp->pp_url_l = encap_list_new(LIST_QUEUE, NULL);
			encap_list_add_str(ppp->pp_url_l,
					   (char *)attr[i + 1],
					   " \t\n");
			continue;
		}

		if (strcmp(attr[i], "options") == 0)
		{
			ppp->pp_opts = strdup((char *)attr[i + 1]);
			continue;
		}

		if (strcmp(attr[i], "from_dir") == 0)
		{
			ppp->pp_from_dir = strdup((char *)attr[i + 1]);
			continue;
		}

		parse_error(psp->ps_parser,
			    "<patch> element: unknown attribute \"%s\"",
			    attr[i]);

	}

	if (profile_elements[psp->ps_el_idx[psp->ps_depth - 1]].el_context
	    == PS_CTX_ENCAP_SOURCE)
	{
		psrcp = (profile_source_t *)psp->ps_el_data[psp->ps_depth - 1];
		pclp = &(psrcp->ps_patches_l);
	}
	else
		pclp = &(psp->ps_profile->ep_patches_l);

	if ((*pclp) == NULL)
		*pclp = encap_list_new(LIST_QUEUE, NULL);

	encap_list_add(*pclp, ppp);
	psp->ps_el_data[psp->ps_depth] = ppp;
}
