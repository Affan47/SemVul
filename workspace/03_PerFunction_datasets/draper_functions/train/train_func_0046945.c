acquire_release_loop(gss_name_t name, int counter, gss_cred_usage_t usage)
{
    OM_uint32 maj_stat, min_stat;
    gss_cred_id_t cred;
    int i;

    for (i = 0; i < counter; i++) {
	maj_stat = gss_acquire_cred(&min_stat, name,
				    GSS_C_INDEFINITE,
				    GSS_C_NO_OID_SET,
				    usage,
				    &cred,
				    NULL,
				    NULL);
	if (maj_stat != GSS_S_COMPLETE)
	    gss_err(1, min_stat, "aquire %d %d != GSS_S_COMPLETE",
		    i, (int)maj_stat);

	maj_stat = gss_release_cred(&min_stat, &cred);
	if (maj_stat != GSS_S_COMPLETE)
	    gss_err(1, min_stat, "release %d %d != GSS_S_COMPLETE",
		    i, (int)maj_stat);
    }
}
