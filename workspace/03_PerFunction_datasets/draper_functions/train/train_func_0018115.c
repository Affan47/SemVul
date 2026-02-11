decoder_query_seeking_fold (const GValue * item, GValue * ret, QueryFold * fold)
{
  GstPad *pad = g_value_get_object (item);

  if (gst_pad_query (pad, fold->query)) {
    gboolean seekable;

    g_value_set_boolean (ret, TRUE);
    gst_query_parse_seeking (fold->query, NULL, &seekable, NULL, NULL);

    GST_DEBUG_OBJECT (item, "got seekable %d", seekable);

    if (fold->seekable == TRUE)
      fold->seekable = seekable;
  }

  return TRUE;
}
