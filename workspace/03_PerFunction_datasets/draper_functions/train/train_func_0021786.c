list_cameras_action (GPParams *p)
{
	int r = GP_OK, n, i;
	CameraAbilities a;

	r = gp_abilities_list_count (gp_params_abilities_list(p));
	if (r < 0)
		return (r);
	if (p->flags & FLAGS_QUIET)
		printf ("%i\n", r);
	else {
		printf (_("Number of supported cameras: %i\n"), r);
		printf (_("Supported cameras:\n"));
	}
	n = r;
	for (i = 0; i < n; i++) {
		r = gp_abilities_list_get_abilities (gp_params_abilities_list(p),
						     i, &a);
		if (r < 0)
			break;
		if (p->flags & FLAGS_QUIET)
			printf ("%s\n", a.model);
		else
			switch (a.status) {
			case GP_DRIVER_STATUS_TESTING:
				printf (_("\t\"%s\" (TESTING)\n"), a.model);
				break;
			case GP_DRIVER_STATUS_EXPERIMENTAL:
				printf (_("\t\"%s\" (EXPERIMENTAL)\n"),
					a.model);
				break;
			case GP_DRIVER_STATUS_PRODUCTION:
			default:
				printf (_("\t\"%s\"\n"), a.model);
				break;
			}
	}

	return (r);
}
