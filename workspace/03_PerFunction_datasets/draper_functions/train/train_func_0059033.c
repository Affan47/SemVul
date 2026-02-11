open_session_request_cb (CamSL * sl, CamSLSession * session,
    CamSLResourceStatus * status)
{
  CamAL *al = CAM_AL (sl->user_data);
  CamALApplication *application;
  guint resource_id = session->resource_id;
  CamReturn ret;

  application = g_hash_table_lookup (al->applications,
      GINT_TO_POINTER (resource_id));
  if (application == NULL) {
    *status = CAM_SL_RESOURCE_STATUS_NOT_FOUND;

    return CAM_RETURN_OK;
  }

  if (CAM_AL_RESOURCE_ID_VERSION (application->resource_id)
      < CAM_AL_RESOURCE_ID_VERSION (resource_id)) {
    *status = CAM_SL_RESOURCE_STATUS_INVALID_VERSION;

    return CAM_RETURN_OK;
  }

  ret = application->session_request (application, session, status);
  if (CAM_FAILED (ret)) {
    *status = CAM_SL_RESOURCE_STATUS_NOT_FOUND;

    return ret;
  }

  if (*status == CAM_SL_RESOURCE_STATUS_OPEN) {
    session->user_data = application;
    application->sessions = g_list_append (application->sessions, session);
  }

  return CAM_RETURN_OK;
}
