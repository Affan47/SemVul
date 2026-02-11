auditd_tcp_listen_uninit ( struct ev_loop *loop,
				struct daemon_conf *config )
{
#ifdef USE_GSSAPI
	OM_uint32 status;
#endif

	ev_io_stop ( loop, &tcp_listen_watcher );
	close ( listen_socket );

#ifdef USE_GSSAPI
	if (use_gss) {
		use_gss = 0;
		gss_release_cred(&status, &server_creds);
	}
#endif

	while (client_chain) {
		unsigned char ack[AUDIT_RMW_HEADER_SIZE];

		AUDIT_RMW_PACK_HEADER (ack, 0, AUDIT_RMW_TYPE_ENDING, 0, 0);
		client_ack (client_chain, ack, "");
		ev_io_stop (loop, &client_chain->io);
		close_client (client_chain);
	}

	if (config->tcp_client_max_idle)
		ev_periodic_stop (loop, &periodic_watcher);
}
