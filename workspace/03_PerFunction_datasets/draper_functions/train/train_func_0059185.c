ftp_lite_close( struct ftp_lite_server *s )
{
	#ifdef HAS_GLOBUS_GSS
		OM_uint32 major;

		if(s->context!=GSS_C_NO_CONTEXT) {
			gss_delete_sec_context(&major,&s->context,GSS_C_NO_BUFFER);
		}
		if(s->credential!=GSS_C_NO_CREDENTIAL) {
			gss_release_cred(&major,&s->credential);
		}
	#endif

	network_close(fileno(s->command));
	fclose(s->command);
	fclose(s->response);
	free(s->hostname);
	free(s);
}
