external_client_plug_init(const sasl_utils_t *utils,
			      int max_version,
			      int *out_version,
			      sasl_client_plug_t **pluglist,
			      int *plugcount)
{
    if (!utils || !out_version || !pluglist || !plugcount)
	return SASL_BADPARAM;

    if (max_version != SASL_CLIENT_PLUG_VERSION) {
	SETERROR( utils, "EXTERNAL version mismatch" );
	return SASL_BADVERS;
    }

    *out_version = SASL_CLIENT_PLUG_VERSION;
    *pluglist = external_client_plugins;
    *plugcount = 1;

    return SASL_OK;
}
