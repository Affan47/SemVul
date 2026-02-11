Context_Error_String(void)
{
  static char buff[256];

  sprintf(buff, "%s", atom_tbl[cur_bip_func].name);
  if (cur_bip_arity >= 0)
    sprintf(buff + strlen(buff), "/%d", cur_bip_arity);

  return buff;
}
