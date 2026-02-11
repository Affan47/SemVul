cdio_mmssff_to_lba (const char *psz_mmssff)
{
  int psz_field;
  lba_t ret;
  char c;

  if (0 == strcmp (psz_mmssff, "0"))
    return 0;

  c = *psz_mmssff++;
  if(c >= '0' && c <= '9')
    psz_field = (c - '0');
  else
    return CDIO_INVALID_LBA;
  while(':' != (c = *psz_mmssff++)) {
    if(c >= '0' && c <= '9')
      psz_field = psz_field * 10 + (c - '0');
    else
      return CDIO_INVALID_LBA;
  }

  ret = cdio_msf3_to_lba (psz_field, 0, 0);

  c = *psz_mmssff++;
  if(c >= '0' && c <= '9')
    psz_field = (c - '0');
  else
    return CDIO_INVALID_LBA;
  if(':' != (c = *psz_mmssff++)) {
    if(c >= '0' && c <= '9') {
      psz_field = psz_field * 10 + (c - '0');
      c = *psz_mmssff++;
      if(c != ':')
	return CDIO_INVALID_LBA;
    }
    else
      return CDIO_INVALID_LBA;
  }

  if(psz_field >= CDIO_CD_SECS_PER_MIN)
    return CDIO_INVALID_LBA;

  ret += cdio_msf3_to_lba (0, psz_field, 0);

  c = *psz_mmssff++;
  if (isdigit(c))
    psz_field = (c - '0');
  else
    return -1;
  if('\0' != (c = *psz_mmssff++)) {
    if (isdigit(c)) {
      psz_field = psz_field * 10 + (c - '0');
      c = *psz_mmssff++;
    }
    else
      return CDIO_INVALID_LBA;
  }

  if('\0' != c)
    return CDIO_INVALID_LBA;

  if(psz_field >= CDIO_CD_FRAMES_PER_SEC)
    return CDIO_INVALID_LBA;

  ret += psz_field;

  return ret;
}
