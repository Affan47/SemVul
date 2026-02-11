_iodbcdm_cfg_savefile (const char *savefile, void *conn_str, int wide)
{
  int ret = 0;
  PCONFIG pconfig;
  BOOL atsection = FALSE;


  if (_iodbcdm_cfg_init_str (&pconfig, conn_str, SQL_NTS, wide) == -1)
    return -1;


  _iodbcdm_cfg_write (pconfig, "ODBC", "PWD", NULL);
  _iodbcdm_cfg_write (pconfig, "ODBC", "FILEDSN", NULL);
  _iodbcdm_cfg_write (pconfig, "ODBC", "SAVEFILE", NULL);
  _iodbcdm_cfg_write (pconfig, "ODBC", "DSN", NULL);


  SQLWriteFileDSN (savefile, "ODBC", "DSN", NULL);
  _iodbcdm_cfg_rewind (pconfig);
  while (_iodbcdm_cfg_nextentry (pconfig) == 0)
    {
      if (atsection)
	{
	  if (_iodbcdm_cfg_section (pconfig))
	    {

              break;
            }
	  else if (_iodbcdm_cfg_define (pconfig))
	    {
              if (!SQLWriteFileDSN (savefile, "ODBC",
				    pconfig->id, pconfig->value))
		{
		  ret = -1;
		  break;
		}
	    }
	}
      else if (_iodbcdm_cfg_section (pconfig)
	  && !strcasecmp (pconfig->section, "ODBC"))
	atsection = TRUE;
    }

  _iodbcdm_cfg_done (pconfig);
  return ret;
}
