fs_raw_conference_init (FsRawConference *conf)
{
  GST_DEBUG_OBJECT (conf, "fs_raw_conference_init");

  conf->priv = FS_RAW_CONFERENCE_GET_PRIVATE (conf);

  conf->priv->max_session_id = 1;

  conf->priv->threads = g_ptr_array_new ();
}
