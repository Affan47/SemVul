cmd_bdat2 (siobuf_t conn, smtp_session_t session)
{
  const char *chunk;
  int len;


  errno = 0;
  chunk = msg_getb (session->msg_source, &len);
  if (chunk != NULL)
    {

      if (session->event_cb != NULL)
	(*session->event_cb) (session, SMTP_EV_MESSAGEDATA,
	                      session->event_cb_arg,
	                      session->current_message, len);
      sio_printf (conn, "BDAT %d\r\n", len);
      sio_write (conn, chunk, len);


      session->cmd_state = session->bdat_abort_pipeline ? -1 : S_bdat2;
    }
  else
    {

      if (session->extensions & EXT_XEXCH50)
	sio_write (conn, "BDAT 2 LAST\r\n\r\n", -1);
      else
	sio_write (conn, "BDAT 0 LAST\r\n", -1);
      sio_set_timeout (conn, session->data2_timeout);
      session->bdat_last_issued = 1;
      session->cmd_state = -1;
    }
  session->bdat_pipelined += 1;
  if (errno != 0)
    {
      set_errno (errno);
      session->cmd_state = session->rsp_state = -1;
    }
}
