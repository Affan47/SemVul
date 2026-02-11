dvb_base_bin_pat_info_cb (DvbBaseBin * dvbbasebin, GstStructure * pat_info)
{
  DvbBaseBinProgram *program;
  DvbBaseBinStream *stream;
  const GValue *value;
  GstStructure *program_info;
  guint program_number;
  guint pid;
  guint old_pmt_pid;
  gint i;
  gboolean rebuild_filter = FALSE;
  const GValue *programs;

  programs = gst_structure_get_value (pat_info, "programs");
  for (i = 0; i < gst_value_list_get_size (programs); ++i) {
    value = gst_value_list_get_value (programs, i);
    program_info = g_value_get_boxed (value);

    gst_structure_get_uint (program_info, "program-number", &program_number);
    gst_structure_get_uint (program_info, "pid", &pid);

    program = dvb_base_bin_get_program (dvbbasebin, program_number);
    if (program == NULL)
      program = dvb_base_bin_add_program (dvbbasebin, program_number);

    old_pmt_pid = program->pmt_pid;
    program->pmt_pid = pid;

    if (program->selected) {

      if (old_pmt_pid != G_MAXUINT16 && old_pmt_pid != program->pmt_pid)
        dvb_base_bin_get_stream (dvbbasebin, old_pmt_pid)->usecount -= 1;

      stream = dvb_base_bin_get_stream (dvbbasebin, program->pmt_pid);
      if (stream == NULL)
        stream = dvb_base_bin_add_stream (dvbbasebin, program->pmt_pid);

      stream->usecount += 1;

      rebuild_filter = TRUE;
    }
  }

  if (rebuild_filter)
    dvb_base_bin_rebuild_filter (dvbbasebin);
}
