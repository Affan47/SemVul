cluster_option_ok (int ci)
{
    int i, found = 0;

    for (i=0; gretl_opts[i].ci; i++) {
	if (gretl_opts[i].ci == ci) {
	    if (gretl_opts[i].o == OPT_C &&
		!strcmp(gretl_opts[i].longopt, "cluster")) {
		return 1;
	    }
	    found = 1;
	} else if (found) {
	    break;
	}
    }

    return 0;
}
