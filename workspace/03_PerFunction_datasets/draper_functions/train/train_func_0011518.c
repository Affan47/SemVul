dvb_base_bin_rebuild_filter (DvbBaseBin * dvbbasebin)
{
  g_hash_table_foreach (dvbbasebin->streams,
      foreach_stream_build_filter, dvbbasebin);

  if (dvbbasebin->filter == NULL)

    dvbbasebin->filter = g_strdup ("");

  GST_INFO_OBJECT (dvbbasebin, "rebuilt filter %s", dvbbasebin->filter);


  g_object_set (dvbbasebin->dvbsrc, "pids", dvbbasebin->filter, NULL);
  g_free (dvbbasebin->filter);
  dvbbasebin->filter = NULL;
}
