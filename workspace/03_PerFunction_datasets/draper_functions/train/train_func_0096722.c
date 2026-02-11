ftp_lite_data_channel_auth( struct ftp_lite_server *s, FILE *data )
{
	OM_uint32 major, minor, flags=0;
	int token;

	if(!s->data_channel_authentication) return 1;

	setbuf(data,0);

	debug(D_FTP,"data channel authentication in progress...");

	major = globus_gss_assist_init_sec_context( &minor, s->credential, &s->data_context, 0, 0, &flags, &token, globus_gss_assist_token_get_fd, data, globus_gss_assist_token_send_fd, data );
	if( major!=GSS_S_COMPLETE ) {
		char *reason;
		globus_gss_assist_display_status_str(&reason,"",major,minor,token);
		if(!reason) reason = strdup("unknown error");
		debug(D_FTP,"data channel authentication failed: %s",reason);
		free(reason);
		errno = EACCES;
		return 0;
	}

	gss_delete_sec_context(&major,&s->data_context,GSS_C_NO_BUFFER);

	debug(D_FTP,"data channel authentication succeeded");

	return 1;

}
