mpegts_base_activate_program (MpegTSBase * base, MpegTSBaseProgram * program,
    guint16 pmt_pid, GstMpegTsSection * section, const GstMpegTsPMT * pmt,
    gboolean initial_program)
{
  guint i;
  MpegTSBaseClass *klass;

  if (G_UNLIKELY (program->active))
    return;

  GST_DEBUG ("Activating program %d", program->program_number);


  if (program->section)
    gst_mpegts_section_unref (program->section);
  program->section = gst_mpegts_section_ref (section);

  program->pmt = pmt;
  program->pmt_pid = pmt_pid;
  program->pcr_pid = pmt->pcr_pid;


  program->registration_id =
      get_registration_from_descriptors (pmt->descriptors);
  GST_DEBUG ("program 0x%04x, registration_id %" SAFE_FOURCC_FORMAT,
      program->program_number, SAFE_FOURCC_ARGS (program->registration_id));

  for (i = 0; i < pmt->streams->len; ++i) {
    GstMpegTsPMTStream *stream = g_ptr_array_index (pmt->streams, i);

    switch (stream->stream_type) {
      case GST_MPEG_TS_STREAM_TYPE_PRIVATE_SECTIONS:
      case GST_MPEG_TS_STREAM_TYPE_MHEG:
      case GST_MPEG_TS_STREAM_TYPE_DSM_CC:
      case GST_MPEG_TS_STREAM_TYPE_DSMCC_A:
      case GST_MPEG_TS_STREAM_TYPE_DSMCC_B:
      case GST_MPEG_TS_STREAM_TYPE_DSMCC_C:
      case GST_MPEG_TS_STREAM_TYPE_DSMCC_D:
      case GST_MPEG_TS_STREAM_TYPE_SL_FLEXMUX_SECTIONS:
      case GST_MPEG_TS_STREAM_TYPE_METADATA_SECTIONS:

        if (base->parse_private_sections)
          MPEGTS_BIT_SET (base->known_psi, stream->pid);
        break;
      default:
        if (G_UNLIKELY (MPEGTS_BIT_IS_SET (base->is_pes, stream->pid)))
          GST_FIXME
              ("Refcounting issue. Setting twice a PID (0x%04x) as known PES",
              stream->pid);
        if (G_UNLIKELY (MPEGTS_BIT_IS_SET (base->known_psi, stream->pid))) {
          GST_FIXME
              ("Refcounting issue. Setting a known PSI PID (0x%04x) as known PES",
              stream->pid);
          MPEGTS_BIT_UNSET (base->known_psi, stream->pid);
        }

        MPEGTS_BIT_SET (base->is_pes, stream->pid);
        break;
    }
    mpegts_base_program_add_stream (base, program,
        stream->pid, stream->stream_type, stream);

  }


  mpegts_base_program_add_stream (base, program, pmt->pcr_pid, -1, NULL);
  MPEGTS_BIT_SET (base->is_pes, pmt->pcr_pid);

  program->active = TRUE;
  program->initial_program = initial_program;

  klass = GST_MPEGTS_BASE_GET_CLASS (base);
  if (klass->program_started != NULL)
    klass->program_started (base, program);

  GST_DEBUG_OBJECT (base, "new pmt activated");
}
