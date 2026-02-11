phoneprofile_load(const char *configname, gn_error error, struct gn_statemachine **state)
{
	*state = NULL;

	if (error == GN_ERR_NONE) {

		*state = malloc(sizeof(**state));
		if (*state) {
			memset(*state, 0, sizeof(**state));


			error = gn_cfg_phone_load(configname, *state);
		} else {
			error = GN_ERR_MEMORYFULL;
		}
	}
	if (error != GN_ERR_NONE) {
		gn_lib_phoneprofile_free(state);
		gn_lib_library_free();
		return error;
	}
	return LASTERROR((*state), GN_ERR_NONE);
}
