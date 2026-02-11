mpegts_parse_finalize (GObject * object)
{
  MpegTSParse2 *parse = GST_MPEGTS_PARSE (object);

  g_free (parse->program_numbers);

  if (G_OBJECT_CLASS (parent_class)->finalize)
    G_OBJECT_CLASS (parent_class)->finalize (object);
}
