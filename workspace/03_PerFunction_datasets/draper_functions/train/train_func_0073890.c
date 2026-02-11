fs_raw_session_new (FsMediaType media_type,
    FsRawConference *conference,
    guint id,
    GError **error)
{
  FsRawSession *session = g_object_new (FS_TYPE_RAW_SESSION,
      "media-type", media_type,
      "conference", conference,
      "id", id,
      NULL);

  if (!session)
  {
    *error = g_error_new (FS_ERROR, FS_ERROR_CONSTRUCTION,
        "Could not create object");
  }
  else if (session->priv->construction_error)
  {
    g_propagate_error (error, session->priv->construction_error);
    g_object_unref (session);
    return NULL;
  }

  return session;
}
