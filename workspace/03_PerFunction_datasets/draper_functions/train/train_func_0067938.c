system_supports_method (equation_system *sys, int method)
{
    if (sys != NULL) {
	int i;

	for (i=0; i<sys->neqns; i++) {
	    if (gretl_list_has_separator(sys->lists[i])) {
		return method == SYS_METHOD_TSLS ||
		    method == SYS_METHOD_3SLS;
	    }
	}
    }

    return 1;
}
