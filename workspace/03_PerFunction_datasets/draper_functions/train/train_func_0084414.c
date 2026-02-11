dvb_base_bin_add_program (DvbBaseBin * dvbbasebin, gint program_number)
{
  DvbBaseBinProgram *program;

  program = g_new0 (DvbBaseBinProgram, 1);
  program->program_number = program_number;
  program->selected = FALSE;
  program->active = FALSE;
  program->pmt_pid = G_MAXUINT16;
  program->pcr_pid = G_MAXUINT16;
  program->pmt = NULL;
  program->old_pmt = NULL;

  g_hash_table_insert (dvbbasebin->programs,
      GINT_TO_POINTER (program_number), program);

  return program;
}
