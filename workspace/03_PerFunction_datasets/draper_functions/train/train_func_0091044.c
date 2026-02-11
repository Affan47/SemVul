fosfat_diskauto (fosfat_t *fosfat)
{
  int i, loop = 1;
  int fboot = -1;
  fosfat_disk_t res = FOSFAT_ED;
  fosfat_bd_t *sys_list;
  fosfat_bl_t *first_bl;

  if (!fosfat)
    return FOSFAT_ED;

  fosfat->fosboot = FOSBOOT_FD;


  for (i = 0; loop && i < 2; i++)
  {
    sys_list = fosfat_read_bd (fosfat, FOSFAT_SYSLIST);
    fosfat->foschk = 0;
    first_bl = fosfat_read_bl (fosfat, FOSFAT_SYSLIST + 1);
    fosfat->foschk = 0;

    if (sys_list && first_bl
        && !strncmp ((char *) sys_list->chk, (char *) first_bl->chk,
                     sizeof (sys_list->chk))
        && c2l (*sys_list->pts, sizeof (*sys_list->pts))
        == FOSFAT_SYSLIST + 1)
    {
      loop = 0;
      fboot = fosfat->fosboot;
    }

    if (sys_list)
      free (sys_list);
    if (first_bl)
      free (first_bl);

    if (loop && !i)
      fosfat->fosboot = FOSBOOT_HD;
  }


  switch (fboot)
  {
  case FOSBOOT_FD:
    res = FOSFAT_FD;
    break;

  case FOSBOOT_HD:
    res = FOSFAT_HD;
    break;

  default:
    res = FOSFAT_ED;
  }


  fosfat->fosboot = -1;

  return res;
}
