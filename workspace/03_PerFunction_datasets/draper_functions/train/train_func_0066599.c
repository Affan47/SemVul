AcceptAndMonitor(giopConnection::notifyReadable_t func,
			      void* cookie) {

  OMNIORB_ASSERT(pd_socket != RC_INVALID_SOCKET);

  pd_callback_func = func;
  pd_callback_cookie = cookie;
  setSelectable(1,0,0);

  while (pd_go) {
    pd_new_conn_socket = RC_INVALID_SOCKET;
    if (!Select()) break;
    if (pd_new_conn_socket != RC_INVALID_SOCKET) {

      ::SSL* ssl = SSL_new(pd_ctx->get_SSL_CTX());
      SSL_set_fd(ssl, pd_new_conn_socket);
      SSL_set_accept_state(ssl);

      if (omniORB::trace(25)) {
	omniORB::logger log;
	CORBA::String_var peer = peerAddress(pd_new_conn_socket);
	log << "Perform SSL accept for new incoming connection " << peer
	    << "\n";
      }

      unsigned long deadline_secs, deadline_nanosecs;
      struct timeval tv;

      if (sslTransportImpl::sslAcceptTimeOut.secs ||
	  sslTransportImpl::sslAcceptTimeOut.nanosecs) {

	SocketSetnonblocking(pd_new_conn_socket);
	omni_thread::get_time(&deadline_secs, &deadline_nanosecs,
			      sslTransportImpl::sslAcceptTimeOut.secs,
			      sslTransportImpl::sslAcceptTimeOut.nanosecs);
      }

      int timeout = 0;
      int go = pd_go;

      while(go && pd_go) {
	if (setAndCheckTimeout(deadline_secs, deadline_nanosecs, tv)) {

	  timeout = 1;
	  break;
	}

	int result = SSL_accept(ssl);
	int code = SSL_get_error(ssl, result);

	switch(code) {
	case SSL_ERROR_NONE:
	  SocketSetblocking(pd_new_conn_socket);
	  return new sslConnection(pd_new_conn_socket,ssl,this);

	case SSL_ERROR_WANT_READ:
	  if (waitRead(pd_new_conn_socket, tv) == 0) {
	    timeout = 1;
	    go = 0;
	  }
	  continue;

	case SSL_ERROR_WANT_WRITE:
	  if (waitWrite(pd_new_conn_socket, tv) == 0) {
	    timeout = 1;
	    go = 0;
	  }
	  continue;

	case SSL_ERROR_SYSCALL:
	  {
	    if (ERRNO == RC_EINTR)
	      continue;
	  }

	case SSL_ERROR_SSL:
	case SSL_ERROR_ZERO_RETURN:
	  {
	    if (omniORB::trace(10)) {
	      omniORB::logger log;
	      char buf[128];
	      ERR_error_string_n(ERR_get_error(),buf,128);
	      CORBA::String_var peer = peerAddress(pd_new_conn_socket);
	      log << "openSSL error detected in SSL accept from "
		  << peer << " : " << (const char*) buf << "\n";
	    }
	    go = 0;
	  }
	}
      }
      if (timeout && omniORB::trace(10)) {
	omniORB::logger log;
	CORBA::String_var peer = peerAddress(pd_new_conn_socket);
	log << "Timeout in SSL accept from " << peer << "\n";
      }
      SSL_free(ssl);
      CLOSESOCKET(pd_new_conn_socket);
    }
  }
  return 0;
}
