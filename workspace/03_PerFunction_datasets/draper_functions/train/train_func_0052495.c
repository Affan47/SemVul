connection_cleanup(Connection *conn)
{
	bind_credentials_clear( conn, PR_FALSE ,
							PR_TRUE  );
	slapi_ch_free((void**)&conn->c_authtype);


	factory_destroy_extension(connection_type,conn,NULL,&(conn->c_extension));


#ifdef _WIN32
	if (conn->c_prfd && (conn->c_flags & CONN_FLAG_SSL))
	{
		LDAPDebug( LDAP_DEBUG_CONNS,
		  "conn=%" PRIu64 " fd=%d closed now\n",
		  conn->c_connid, conn->c_sd,0);
		PR_Close(conn->c_prfd);
	}
	else if (conn->c_sd)
	{
		LDAPDebug( LDAP_DEBUG_CONNS,
		  "conn=%" PRIu64 " fd=%d closed now\n",
		  conn->c_connid, conn->c_sd,0);
		closesocket(conn->c_sd);
	}
#else
	if (conn->c_prfd)
	{
		PR_Close(conn->c_prfd);
	}
#endif

	conn->c_sd= SLAPD_INVALID_SOCKET;
	conn->c_ldapversion= 0;

    conn->c_isreplication_session = 0;
	slapi_ch_free((void**)&conn->cin_addr );
	slapi_ch_free((void**)&conn->cin_destaddr );
    if ( conn->c_domain != NULL )
    {
		ber_bvecfree( conn->c_domain );
		conn->c_domain = NULL;
    }

	conn->c_gettingber= 0;
	conn->c_currentber= NULL;
	conn->c_starttime= 0;
	conn->c_connid= 0;
	conn->c_opsinitiated= 0;
	conn->c_opscompleted= 0;
	conn->c_threadnumber= 0;
	conn->c_refcnt= 0;
	conn->c_idlesince= 0;
	conn->c_flags= 0;
	conn->c_needpw= 0;
	conn->c_prfd= NULL;

	conn->c_fdi= SLAPD_INVALID_SOCKET_INDEX;
	conn->c_next= NULL;
	conn->c_prev= NULL;
	conn->c_extension= NULL;
	conn->c_ssl_ssf = 0;
	conn->c_local_ssf = 0;
	conn->c_unix_local = 0;

	sasl_dispose((sasl_conn_t**)&conn->c_sasl_conn);

	handle_closed_connection(conn);
	pagedresults_cleanup(conn, 0 );


	connection_free_private_buffer(conn);
}
