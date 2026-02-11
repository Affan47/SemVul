dvb_base_bin_activate_program (DvbBaseBin * dvbbasebin,
    DvbBaseBinProgram * program)
{
  DvbBaseBinStream *stream;

  if (program->old_pmt) {
    dvb_base_bin_remove_pmt_streams (dvbbasebin, program->old_pmt);
    dvbbasebin->pmtlist = g_list_remove (dvbbasebin->pmtlist, program->old_pmt);
  }


  if (!program->pmt_active) {
    stream = dvb_base_bin_get_stream (dvbbasebin, program->pmt_pid);
    if (stream == NULL)
      stream = dvb_base_bin_add_stream (dvbbasebin, program->pmt_pid);
    stream->usecount += 1;
    program->pmt_active = TRUE;
  }

  if (program->pmt) {
    guint16 old_pcr_pid;

    old_pcr_pid = program->pcr_pid;
    program->pcr_pid = program->pmt->pcr_pid;
    if (old_pcr_pid != G_MAXUINT16 && old_pcr_pid != program->pcr_pid)
      dvb_base_bin_get_stream (dvbbasebin, old_pcr_pid)->usecount--;

    stream = dvb_base_bin_get_stream (dvbbasebin, program->pcr_pid);
    if (stream == NULL)
      stream = dvb_base_bin_add_stream (dvbbasebin, program->pcr_pid);
    stream->usecount += 1;

    dvb_base_bin_add_pmt_streams (dvbbasebin, program->pmt);
    dvbbasebin->pmtlist =
        g_list_append (dvbbasebin->pmtlist, (gpointer) program->pmt);
    dvbbasebin->pmtlist_changed = TRUE;
    program->active = TRUE;
  }

  dvb_base_bin_rebuild_filter (dvbbasebin);
}
