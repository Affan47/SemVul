gss_check(int sock)
{
	struct sockaddr_in remote, local;
	socklen_t       addrlen;
	char           *name;

	gss_buffer_desc input_token, output_token;
	gss_cred_id_t   delegated_cred_handle = GSS_C_NO_CREDENTIAL;
	OM_uint32       maj_stat, min_stat;
	gss_name_t      client_name;
	gss_buffer_desc export_name;
	gss_channel_bindings_t input_chan_bindings;

	tunnel_ctx_t* tunnel_ctx = createGssContext(sock);
	if( tunnel_ctx == NULL ) {
		return -1;
	}

#ifndef MIT_KRB5
# if 0
	delegated_cred_handle = malloc(sizeof(*delegated_cred_handle));
	memset((char *) delegated_cred_handle, 0,
	       sizeof(*delegated_cred_handle));
# endif
#endif


	addrlen = sizeof(local);
	if (getsockname(sock, (struct sockaddr *) & local, &addrlen) < 0
	    || addrlen != sizeof(local)) {
#ifdef SHOW_ERROR
		perror("getsockname");
#endif
		return -1;
	}
	addrlen = sizeof(remote);
	if (getpeername(sock, (struct sockaddr *) & remote, &addrlen) < 0
	    || addrlen != sizeof(remote)) {
#ifdef SHOW_ERROR
		perror("getpeername");
#endif
		return -1;
	}
	input_chan_bindings = malloc(sizeof(struct gss_channel_bindings_struct));

	sockaddr_to_gss_address((struct sockaddr *) & local,
				&input_chan_bindings->initiator_addrtype,
				&input_chan_bindings->initiator_address);
	sockaddr_to_gss_address((struct sockaddr *) & remote,
				&input_chan_bindings->acceptor_addrtype,
				&input_chan_bindings->acceptor_address);

	input_chan_bindings->application_data.length = 0;
	input_chan_bindings->application_data.value = NULL;

	do {

		input_token.value = malloc(MAXBUF);
		input_token.length = eRead(sock, input_token.value, MAXBUF);

		maj_stat = gss_accept_sec_context(&min_stat,
						  &tunnel_ctx->context_hdl,
						  GSS_C_NO_CREDENTIAL,
						  &input_token,
						  input_chan_bindings,
						  &client_name,
						  NULL,
						  &output_token,
						  NULL,
						  NULL,
						  &delegated_cred_handle);

		if (GSS_ERROR(maj_stat)) {
			gss_print_errors(maj_stat);
		}

		gss_release_buffer(&min_stat, &input_token);

		if (output_token.length != 0) {
			eWrite(sock, output_token.value, output_token.length);
			printf("sended token %d\n", output_token.length);
			gss_release_buffer(&min_stat, &output_token);
		}

		if (maj_stat == GSS_S_COMPLETE) {
			printf("GSS OK\n");
			if (GSS_ERROR(maj_stat)) {
				gss_print_errors(maj_stat);
			}
			maj_stat = gss_export_name(&min_stat, client_name, &export_name);

			if (GSS_ERROR(maj_stat)) {
				gss_print_errors(maj_stat);
			}
			name = realloc(export_name.value, export_name.length + 1);
			name[export_name.length] = '\0';
#if 0
			printf("name = %s\n", name); fflush(stdout);
#endif
		}


	} while( maj_stat == GSS_S_CONTINUE_NEEDED ) ;

	return 0;
}
