pie_dwnld_gamma (Pie_Scanner * scanner)
{
  SANE_Status status;

  DBG (DBG_proc, "pie_dwnld_gamma\n");

  if (scanner->colormode == RGB)
    {
      status =
	pie_dwnld_gamma_one (scanner, FILTER_RED, scanner->gamma_table[1]);
      if (status)
	return status;


      status =
	pie_dwnld_gamma_one (scanner, FILTER_GREEN, scanner->gamma_table[2]);
      if (status)
	return status;

      status =
	pie_dwnld_gamma_one (scanner, FILTER_BLUE, scanner->gamma_table[3]);
      if (status)
	return status;
    }
  else
    {
      SANE_Int *table;


      if (scanner->colormode == GRAYSCALE)
	table = scanner->gamma_table[0];
      else
	table = NULL;

      status = pie_dwnld_gamma_one (scanner, FILTER_GREEN, table);
      if (status)
	return status;
    }

  usleep (DOWNLOAD_GAMMA_WAIT_TIME);

  return SANE_STATUS_GOOD;
}
