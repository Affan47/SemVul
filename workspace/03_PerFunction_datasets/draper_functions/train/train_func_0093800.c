fs_msn_conference_init (FsMsnConference *conf)
{
  GST_DEBUG_OBJECT (conf, "fs_msn_conference_init");

  conf->priv = FS_MSN_CONFERENCE_GET_PRIVATE (conf);
}
