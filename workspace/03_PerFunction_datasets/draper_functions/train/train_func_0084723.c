get_LL_stuff(const struct proj_parm *parm, const struct proj_desc *desc,
		 int lat, double *val)
{
    char answer[200];
    char buff[256];


    if (parm->def_exists == 1) {
	if (lat == 1) {
	    G_format_northing(parm->deflt, buff, PROJECTION_LL);
	    fprintf(stderr, "\n    Enter %s (%s) :", desc->desc, buff);
	}
	else {
	    G_format_easting((parm->deflt), buff, PROJECTION_LL);
	    fprintf(stderr, "\n    Enter %s (%s) :", desc->desc, buff);
	}
	G_gets(answer);
	if (strlen(answer) == 0) {
	    *val = parm->deflt;
	    return (1);
	}
    }
    else {
	fprintf(stderr, "\n    Enter %s :", desc->desc);
	G_gets(answer);
	if (strlen(answer) == 0) {
	    *val = 0.0;
	    return (0);
	}
    }
    if (lat == 1) {
	if (!get_deg(answer, 1)) {
	    return (0);
	}
    }
    else {
	if (!get_deg(answer, 0)) {
	    return (0);
	}
    }
    sscanf(answer, "%lf", val);
    return (1);
}
