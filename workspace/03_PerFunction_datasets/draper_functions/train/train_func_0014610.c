_iodbcdm_cfg_to_string (PCONFIG pconfig, char *section,
			char *buf, size_t buf_sz)
{
  BOOL atsection;

  if (_iodbcdm_cfg_rewind (pconfig) == -1)
    return -1;

  atsection = FALSE;
  buf[0] = '\0';
  while (_iodbcdm_cfg_nextentry (pconfig) == 0)
    {
      if (atsection)
        {
          if (_iodbcdm_cfg_section (pconfig))
            break;
          else if (_iodbcdm_cfg_define (pconfig))
            {
              if (buf[0] != '\0')
                CATBUF (buf, ";", buf_sz);
              CATBUF (buf, pconfig->id, buf_sz);
              CATBUF (buf, "=", buf_sz);
              CATBUF (buf, pconfig->value, buf_sz);
            }
        }
      else if (_iodbcdm_cfg_section (pconfig) &&
	       !strcasecmp (pconfig->section, section))
        atsection = TRUE;
    }
  return 0;
}
