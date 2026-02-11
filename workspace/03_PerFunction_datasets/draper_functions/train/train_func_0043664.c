gst_ts_demux_create_tags (TSDemuxStream * stream)
{
  MpegTSBaseStream *bstream = (MpegTSBaseStream *) stream;
  const guint8 *desc = NULL;
  int i;

  desc =
      mpegts_get_descriptor_from_stream (bstream,
      GST_MTS_DESC_ISO_639_LANGUAGE);

  if (!desc) {
    desc =
        mpegts_get_descriptor_from_stream (bstream,
        GST_MTS_DESC_DVB_SUBTITLING);
  }

  if (desc) {
    if (!stream->taglist)
      stream->taglist = gst_tag_list_new_empty ();

    for (i = 0; i < DESC_ISO_639_LANGUAGE_codes_n (desc); i++) {
      const gchar *lc;
      gchar lang_code[4];
      gchar *language_n;

      language_n = (gchar *)
          DESC_ISO_639_LANGUAGE_language_code_nth (desc, i);


      if (!language_n[0] || !language_n[1])
        continue;

      GST_LOG ("Add language code for stream: %s", language_n);

      lang_code[0] = language_n[0];
      lang_code[1] = language_n[1];
      lang_code[2] = language_n[2];
      lang_code[3] = 0;


      lc = gst_tag_get_language_code (lang_code);
      gst_tag_list_add (stream->taglist, GST_TAG_MERGE_REPLACE,
          GST_TAG_LANGUAGE_CODE, (lc) ? lc : lang_code, NULL);
    }
  }
}
