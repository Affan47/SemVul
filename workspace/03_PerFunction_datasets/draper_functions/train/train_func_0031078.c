fs_codec_list_copy (const GList *codec_list)
{
  GQueue copy = G_QUEUE_INIT;
  const GList *lp;

  for (lp = codec_list; lp; lp = g_list_next (lp)) {
    FsCodec *codec = (FsCodec *) lp->data;

    g_queue_push_tail (&copy, fs_codec_copy (codec));
  }

  return copy.head;
}
