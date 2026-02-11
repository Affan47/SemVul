xfrm_tmpl_parse(struct xfrm_user_tmpl *tmpl,
			   int *argcp, char ***argvp)
{
	int argc = *argcp;
	char **argv = *argvp;
	char *idp = NULL;

	while (1) {
		if (strcmp(*argv, "mode") == 0) {
			NEXT_ARG();
			xfrm_mode_parse(&tmpl->mode,  &argc, &argv);
		} else if (strcmp(*argv, "reqid") == 0) {
			NEXT_ARG();
			xfrm_reqid_parse(&tmpl->reqid, &argc, &argv);
		} else if (strcmp(*argv, "level") == 0) {
			NEXT_ARG();

			if (strcmp(*argv, "required") == 0)
				tmpl->optional = 0;
			else if (strcmp(*argv, "use") == 0)
				tmpl->optional = 1;
			else
				invarg("LEVEL value is invalid\n", *argv);

		} else {
			if (idp) {
				PREV_ARG();
				break;
			}
			idp = *argv;
			preferred_family = AF_UNSPEC;
			xfrm_id_parse(&tmpl->saddr, &tmpl->id, &tmpl->family,
				      0, &argc, &argv);
			preferred_family = tmpl->family;
		}

		if (!NEXT_ARG_OK())
			break;

		NEXT_ARG();
	}
	if (argc == *argcp)
		missarg("TMPL");

	*argcp = argc;
	*argvp = argv;

	return 0;
}
