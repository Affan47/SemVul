dvb_base_bin_finalize (GObject * object)
{
  DvbBaseBin *dvbbasebin = GST_DVB_BASE_BIN (object);

  g_hash_table_destroy (dvbbasebin->streams);
  g_hash_table_destroy (dvbbasebin->programs);
  g_list_free (dvbbasebin->pmtlist);

  if (G_OBJECT_CLASS (parent_class)->finalize)
    G_OBJECT_CLASS (parent_class)->finalize (object);
}
