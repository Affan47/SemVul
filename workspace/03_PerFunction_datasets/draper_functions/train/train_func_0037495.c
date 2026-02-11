rosh_ls_arg_opt(int argc, char *argv[], int optarr[])
{
    int rv = 0;

    optarr[0] = -1;
    optarr[1] = -1;
    optarr[2] = -1;
    rosh_getopt_reset();
    while (rv != -1) {
	ROSH_DEBUG2("getopt optind=%d rv=%d\n", optind, rv);
	rv = getopt(argc, argv, rosh_ls_opt_str);
	switch (rv) {
	case 'l':
	case 0:
	    optarr[0] = 1;
	    break;
	case 'F':
	case 1:
	    optarr[1] = 1;
	    break;
	case 'i':
	case 2:
	    optarr[2] = 1;
	    break;
	case '?':
	case -1:
	default:
	    ROSH_DEBUG2("getopt optind=%d rv=%d\n", optind, rv);
	    break;
	}
    }
    ROSH_DEBUG2(" end getopt optind=%d rv=%d\n", optind, rv);
    ROSH_DEBUG2("\tIn rosh_ls_arg_opt() opt[0]=%d\topt[1]=%d\topt[2]=%d\n", optarr[0], optarr[1],
	       optarr[2]);
}
