dvb_base_bin_set_program_numbers (DvbBaseBin * dvbbasebin, const gchar * pn)
{
  gchar **strv, **walk;
  DvbBaseBinProgram *program;


  strv = g_strsplit (pn, ":", 0);

  for (walk = strv; *walk; walk++) {
    gint program_number = strtol (*walk, NULL, 0);

    program = dvb_base_bin_get_program (dvbbasebin, program_number);
    if (program == NULL) {
      program = dvb_base_bin_add_program (dvbbasebin, program_number);
      program->selected = TRUE;
    }
  }

  g_strfreev (strv);


  if (dvbbasebin->program_numbers)
    g_free (dvbbasebin->program_numbers);
  dvbbasebin->program_numbers = g_strdup (pn);

  if (0)
    dvb_base_bin_deactivate_program (dvbbasebin, NULL);
}
