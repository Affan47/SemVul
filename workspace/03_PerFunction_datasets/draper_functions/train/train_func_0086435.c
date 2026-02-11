mpegts_base_steal_program (MpegTSBase * base, gint program_number)
{
  MpegTSBaseProgram *program;

  program = (MpegTSBaseProgram *) g_hash_table_lookup (base->programs,
      GINT_TO_POINTER ((gint) program_number));

  if (program)
    g_hash_table_steal (base->programs,
        GINT_TO_POINTER ((gint) program_number));

  return program;
}
