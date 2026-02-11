mysasl_getrealm_cb(void *context, int id,
			      const char **availrealms __attribute__((unused)),
			      const char **result)
{
    if (id != SASL_CB_GETREALM || !result) {
	return SASL_BADPARAM;
    }

    *result = (char *) context;
    return SASL_OK;
}
