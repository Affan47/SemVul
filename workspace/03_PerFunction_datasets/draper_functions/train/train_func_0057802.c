check_gss_creds(const char *service, const char *hostname)
{
    OM_uint32 maj_stat, min_stat;
    gss_cred_usage_t cu;
    gss_name_t target_name;

    (void)import_name(service, hostname, &target_name, FALSE);
    (void)gss_release_name(&min_stat, &target_name);

    maj_stat = gss_inquire_cred(&min_stat, GSS_C_NO_CREDENTIAL,
	    NULL, NULL, &cu, NULL);
    if (maj_stat != GSS_S_COMPLETE
	    || (cu != GSS_C_INITIATE && cu != GSS_C_BOTH)) {
	if (outlevel >= O_DEBUG) {
	    decode_status("gss_inquire_cred", maj_stat, min_stat, stdout);
	    report(stdout, GT_("No suitable GSSAPI credentials found. Skipping GSSAPI authentication.\n"));
	    report(stdout, GT_("If you want to use GSSAPI, you need credentials first, possibly from kinit.\n"));
	}
	return PS_AUTHFAIL;
    }

    return PS_SUCCESS;
}
