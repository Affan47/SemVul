boolvar_get_flag (const char *s)
{
    if (!strcmp(s, ECHO)) {
	return STATE_ECHO_ON;
    } else if (!strcmp(s, MESSAGES)) {
	return STATE_MSGS_ON;
    } else if (!strcmp(s, WARNINGS)) {
	return STATE_WARN_ON;
    } else if (!strcmp(s, USE_SVD)) {
	return STATE_USE_SVD;
    } else if (!strcmp(s, USE_LBFGS)) {
	return STATE_USE_LBFGS;
    } else if (!strcmp(s, FORCE_DECP)) {
	return STATE_FORCE_DECPOINT;
    } else if (!strcmp(s, USE_CWD)) {
	return STATE_USE_CWD;
    } else if (!strcmp(s, USE_FCP)) {
	return STATE_USE_FCP;
    } else if (!strcmp(s, HALT_ON_ERR)) {
	return STATE_HALT_ON_ERR;
    } else if (!strcmp(s, MAX_VERBOSE)) {
	return STATE_MAX_VERBOSE;
    } else if (!strcmp(s, SHELL_OK)) {
	return STATE_SHELL_OK;
    } else if (!strcmp(s, FORCE_HC)) {
	return STATE_FORCE_HC;
    } else if (!strcmp(s, PREWHITEN)) {
	return STATE_PREWHITEN;
    } else if (!strcmp(s, PCSE)) {
	return STATE_USE_PCSE;
    } else if (!strcmp(s, SKIP_MISSING)) {
	return STATE_SKIP_MISSING;
    } else if (!strcmp(s, BFGS_RSTEP)) {
	return STATE_BFGS_RSTEP;
    } else if (!strcmp(s, DPDSTYLE)) {
	return STATE_DPDSTYLE_ON;
    } else if (!strcmp(s, USE_OPENMP)) {
	return STATE_OPENMP_ON;
    } else {
	fprintf(stderr, "libset_get_bool: unrecognized "
		"variable '%s'\n", s);
	return 0;
    }
}
