proto (int sock, const char *service)
{
    struct sockaddr_in remote, local;
    socklen_t addrlen;
    gss_ctx_id_t context_hdl = GSS_C_NO_CONTEXT;
    gss_buffer_t input_token, output_token;
    gss_buffer_desc real_input_token, real_output_token;
    OM_uint32 maj_stat, min_stat;
    gss_name_t client_name;
    gss_buffer_desc name_token;

    addrlen = sizeof(local);
    if (getsockname (sock, (struct sockaddr *)&local, &addrlen) < 0
	|| addrlen != sizeof(local))
	err (1, "getsockname)");

    addrlen = sizeof(remote);
    if (getpeername (sock, (struct sockaddr *)&remote, &addrlen) < 0
	|| addrlen != sizeof(remote))
	err (1, "getpeername");

    input_token = &real_input_token;
    output_token = &real_output_token;

    do {
	nt_read_token (sock, input_token);
	maj_stat =
	    gss_accept_sec_context (&min_stat,
				    &context_hdl,
				    GSS_C_NO_CREDENTIAL,
				    input_token,
				    GSS_C_NO_CHANNEL_BINDINGS,
				    &client_name,
				    NULL,
				    output_token,
				    NULL,
				    NULL,
				    NULL);
	if(GSS_ERROR(maj_stat))
	    gss_err (1, min_stat, "gss_accept_sec_context");
	if (output_token->length != 0)
	    nt_write_token (sock, output_token);
	if (GSS_ERROR(maj_stat)) {
	    if (context_hdl != GSS_C_NO_CONTEXT)
		gss_delete_sec_context (&min_stat,
					&context_hdl,
					GSS_C_NO_BUFFER);
	    break;
	}
    } while(maj_stat & GSS_S_CONTINUE_NEEDED);

    if (auth_file != NULL) {
	gss_buffer_desc data;

	maj_stat = gsskrb5_extract_authz_data_from_sec_context(&min_stat,
							       context_hdl,
							       KRB5_AUTHDATA_WIN2K_PAC,
							       &data);
	if (maj_stat == GSS_S_COMPLETE) {
	    rk_dumpdata(auth_file, data.value, data.length);
	    gss_release_buffer(&min_stat, &data);
	}
    }

    maj_stat = gss_display_name (&min_stat,
				 client_name,
				 &name_token,
				 NULL);
    if (GSS_ERROR(maj_stat))
	gss_err (1, min_stat, "gss_display_name");

    fprintf (stderr, "User is `%.*s'\n", (int)name_token.length,
	    (char *)name_token.value);


    output_token->value  = strdup ("hejsan");
    output_token->length = strlen (output_token->value) + 1;
    nt_write_token (sock, output_token);

    output_token->value  = strdup ("hoppsan");
    output_token->length = strlen (output_token->value) + 1;
    nt_write_token (sock, output_token);

    return 0;
}
