libset_get_bool (const char *key)
{
    int flag, ret = 0;


    if (!strcmp(key, R_FUNCTIONS)) {
	return R_functions;
    } else if (!strcmp(key, R_LIB)) {
	return R_lib;
    }

    if (!strcmp(key, MAX_VERBOSE) && gretl_debug > 1) {

	return 1;
    }

    if (check_for_state()) {
	return 0;
    }

    maybe_check_env(key);

    flag = boolvar_get_flag(key);
    if (flag == 0) {
	fprintf(stderr, "libset_get_bool: unrecognized "
		"variable '%s'\n", key);
	ret = 0;
    } else {
	ret = flag_to_bool(state, flag);
    }

    return ret;
}
