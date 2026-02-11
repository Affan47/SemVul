mpegts_parse_get_tags_from_sdt (MpegTSParse * parse, GstStructure * sdt_info)
{
  const GValue *services;
  guint i;

  services = gst_structure_get_value (sdt_info, "services");

  for (i = 0; i < gst_value_list_get_size (services); i++) {
    const GstStructure *service;
    const gchar *sid_str;
    gchar *tmp;
    gint program_number;
    MpegTSParseProgram *program;

    service = gst_value_get_structure (gst_value_list_get_value (services, i));


    sid_str = gst_structure_get_name (service);
    tmp = g_strstr_len (sid_str, -1, "-");
    if (!tmp)
      continue;
    program_number = atoi (++tmp);

    program = mpegts_parse_get_program (parse, program_number);
    if (program && program->tspad && !program->tspad->tags) {
      program->tspad->tags = gst_tag_list_new_full (GST_TAG_ARTIST,
          gst_structure_get_string (service, "name"), NULL);
    }
  }
}
