error_gss(enum logcode code, OM_uint32 major, OM_uint32 minor, const char *format, ...)
{
    OM_uint32 maj_stat, min_stat;
    gss_buffer_desc gss_msg = GSS_C_EMPTY_BUFFER;
    OM_uint32 msg_ctx;
    va_list ap;
    char message[BIGPATHBUFLEN];

    va_start(ap, format);
    vsnprintf(message, sizeof message, format, ap);
    va_end(ap);

    msg_ctx = 0;
    if(major != GSS_S_FAILURE)
	do {
	    maj_stat = gss_display_status(&min_stat, major,
					  GSS_C_GSS_CODE, GSS_C_NULL_OID, &msg_ctx, &gss_msg);
	    rprintf(FERROR, "GSS-API error: %s: %s\n", message, (char *) gss_msg.value);
	    free_gss_buffer(&gss_msg);
	} while(msg_ctx != 0);

    if(minor != 0) {
	do {
	    maj_stat = gss_display_status(&min_stat, minor,
					  GSS_C_MECH_CODE, GSS_C_NULL_OID, &msg_ctx, &gss_msg);
	    rprintf(FERROR, "GSS-API error: %s: %s\n",message, (char *) gss_msg.value);
	    free_gss_buffer(&gss_msg);
	} while(msg_ctx != 0);
    }
}
