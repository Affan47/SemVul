gst_wavenc_parse_labl (GstWavEnc * wavenc, guint32 id, GstTocEntry * entry)
{
  gchar *tag;
  GstTagList *tags;
  GstWavEncLabl *labl;

  g_return_val_if_fail (entry != NULL, FALSE);

  tags = gst_toc_entry_get_tags (entry);
  if (!tags) {
    GST_INFO_OBJECT (wavenc, "no tags for entry: %d", id);
    return FALSE;
  }
  if (!gst_tag_list_get_string (tags, GST_TAG_TITLE, &tag)) {
    GST_INFO_OBJECT (wavenc, "no title tag for entry: %d", id);
    return FALSE;
  }

  labl = g_new (GstWavEncLabl, 1);
  memcpy (labl->chunk_id, "labl", 4);
  labl->chunk_data_size = 4 + strlen (tag) + 1;
  labl->cue_point_id = id;
  labl->text = tag;

  GST_DEBUG_OBJECT (wavenc, "got labl: '%s'", tag);

  wavenc->labls = g_list_append (wavenc->labls, labl);

  return TRUE;
}
