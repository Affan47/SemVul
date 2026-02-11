send_close_session_response (CamSL * sl, CamSLSession * session, guint8 status)
{
  CamReturn ret;
  guint8 *tpdu;
  guint size;
  guint offset;
  guint8 *spdu;


  cam_tl_calc_buffer_size (session->sl->tl, 5, &size, &offset);

  tpdu = g_malloc0 (size);
  spdu = tpdu + offset;

  spdu[0] = TAG_OPEN_SESSION_RESPONSE;

  spdu[1] = 3;
  spdu[2] = status;
  GST_WRITE_UINT16_BE (&spdu[3], session->session_nb);

  ret = cam_tl_connection_write (session->connection, tpdu, size, 5);
  g_free (tpdu);
  if (CAM_FAILED (ret))
    return ret;

  return CAM_RETURN_OK;
}
