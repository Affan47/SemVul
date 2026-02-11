auth_gssapi_destroy(AUTH *auth)
{
     struct timeval timeout;
     OM_uint32 gssstat, minor_stat;
     gss_cred_id_t cred;
     int callstat;

     if (AUTH_PRIVATE(auth)->client_handle.length == 0) {
	  PRINTF(("gssapi_destroy: no client_handle, not calling destroy\n"));
	  goto skip_call;
     }

     PRINTF(("gssapi_destroy: marshalling new creds\n"));
     if (!marshall_new_creds(auth, TRUE, &AUTH_PRIVATE(auth)->client_handle)) {
	  PRINTF(("gssapi_destroy: marshall_new_creds failed\n"));
	  goto skip_call;
     }

     PRINTF(("gssapi_destroy: calling GSSAPI_DESTROY\n"));
     timeout.tv_sec = 1;
     timeout.tv_usec = 0;
     callstat = clnt_call(AUTH_PRIVATE(auth)->clnt, AUTH_GSSAPI_DESTROY,
			  xdr_void, NULL, xdr_void, NULL, timeout);
     if (callstat != RPC_SUCCESS)
	  clnt_sperror(AUTH_PRIVATE(auth)->clnt,
		       "gssapi_destroy: GSSAPI_DESTROY failed");

skip_call:
     PRINTF(("gssapi_destroy: deleting context\n"));
     gssstat = gss_delete_sec_context(&minor_stat,
				      &AUTH_PRIVATE(auth)->context,
				      NULL);
     if (gssstat != GSS_S_COMPLETE)
	  AUTH_GSSAPI_DISPLAY_STATUS(("deleting context", gssstat,
				      minor_stat));
     if (AUTH_PRIVATE(auth)->def_cred) {
	  cred = GSS_C_NO_CREDENTIAL;
	  gssstat = gss_release_cred(&minor_stat, &cred);
	  if (gssstat != GSS_S_COMPLETE)
	       AUTH_GSSAPI_DISPLAY_STATUS(("deleting default credential",
					   gssstat, minor_stat));
     }

     free(AUTH_PRIVATE(auth)->client_handle.value);

#if 0
     PRINTF(("gssapi_destroy: calling GSSAPI_EXIT\n"));
     AUTH_PRIVATE(auth)->established = FALSE;
     callstat = clnt_call(AUTH_PRIVATE(auth)->clnt, AUTH_GSSAPI_EXIT,
			  xdr_void, NULL, xdr_void, NULL, timeout);
#endif

     free(auth->ah_private);
     free(auth);
     PRINTF(("gssapi_destroy: done\n"));
}
