import_name(const char *service, const char *hostname,
	gss_name_t *target_name, flag verbose)
{
    char *buf1;
    size_t buf1siz;
    OM_uint32 maj_stat, min_stat;
    gss_buffer_desc request_buf;


    buf1siz = strlen(service) + 1 + strlen(hostname) + 1;
    buf1 = (char *)xmalloc(buf1siz);
    snprintf(buf1, buf1siz, "%s@%s", service, hostname);
    request_buf.value = buf1;
    request_buf.length = strlen(buf1) + 1;
    maj_stat = gss_import_name(&min_stat, &request_buf,
	    GSS_C_NT_HOSTBASED_SERVICE, target_name);
    if (maj_stat != GSS_S_COMPLETE) {
	decode_status("gss_import_name", maj_stat, min_stat, stderr);
        report(stderr, GT_("Couldn't get service name for [%s]\n"), buf1);
        return PS_AUTHFAIL;
    }
    else if (outlevel >= O_DEBUG && verbose) {
        (void)gss_display_name(&min_stat, *target_name, &request_buf, NULL);
        report(stderr, GT_("Using service name [%s]\n"),
	       (char *)request_buf.value);
    }
    (void)gss_release_buffer(&min_stat, &request_buf);

    return PS_SUCCESS;
}
