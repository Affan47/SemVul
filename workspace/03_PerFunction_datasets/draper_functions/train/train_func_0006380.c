handle_create_session_response (CamSL * sl, CamTLConnection * connection,
    guint8 * spdu, guint spdu_length)
{
  guint16 session_nb;
  CamSLSession *session;


  if (spdu_length != 9) {
    GST_ERROR ("expected CREATE_SESSION_RESPONSE to be 9 bytes, got %d",
        spdu_length);
    return CAM_RETURN_SESSION_ERROR;
  }


  session_nb = GST_READ_UINT16_BE (&spdu[7]);

  session = g_hash_table_lookup (sl->sessions,
      GINT_TO_POINTER ((guint) session_nb));
  if (session == NULL) {
    GST_DEBUG ("got CREATE_SESSION_RESPONSE for unknown session: %d",
        session_nb);
    return CAM_RETURN_SESSION_ERROR;
  }

  if (session->state == CAM_SL_SESSION_STATE_CLOSING) {
    GST_DEBUG ("ignoring CREATE_SESSION_RESPONSE for closing session: %d",
        session_nb);
    return CAM_RETURN_OK;
  }

  session->state = CAM_SL_SESSION_STATE_ACTIVE;

  GST_DEBUG ("session opened %d", session->session_nb);

  if (sl->session_opened)

    return sl->session_opened (sl, session);
  return CAM_RETURN_OK;
}
