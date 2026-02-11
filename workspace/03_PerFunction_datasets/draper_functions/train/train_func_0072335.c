rsp_auth (siobuf_t conn, smtp_session_t session)
{
  int code;

  code = read_smtp_response (conn, session, &session->mta_status, NULL);
  if (code < 0)
    {
      session->rsp_state = S_quit;
      return;
    }
  if (code == 4 || code == 5)
    {


      if (session->mta_status.code == 534 || session->mta_status.code == 538)
	session->rsp_state = S_quit;
      else
        {


	  if (next_auth_mechanism (session))
	    session->rsp_state = S_auth;
#ifdef USE_ETRN
	  else if (check_etrn (session))
	    session->rsp_state = S_etrn;
#endif
	  else
	    session->rsp_state = initial_transaction_state (session);
        }
    }
  else if (code == 2)
    {
      session->authenticated = 1;
      if (auth_get_ssf (session->auth_context) != 0)
        {


	  sio_set_securitycb (conn, auth_encode, auth_decode,
	  		      session->auth_context);
	  session->auth_context = NULL;
	  session->extensions = 0;
	  session->rsp_state = S_ehlo;
        }
#ifdef USE_ETRN
      else if (check_etrn (session))
	session->rsp_state = S_etrn;
#endif
      else
	session->rsp_state = initial_transaction_state (session);
    }
  else if (code == 3)
    session->rsp_state = S_auth2;
  else
    {
      set_error (SMTP_ERR_INVALID_RESPONSE_STATUS);
      session->rsp_state = S_quit;
    }
}
