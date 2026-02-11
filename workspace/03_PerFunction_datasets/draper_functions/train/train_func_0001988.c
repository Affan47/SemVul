lf_read_pre_raw_newline(
  pnmState *pnm,
  byte *data,
  int len)
{
  while(pnm->pos < len && data[pnm->pos] != '\n' && data[pnm->pos] != '\r')
    pnm->pos++;
  if(pnm->pos >= len) return PNM_NEED_DATA;
  if(pnm->mac_newlines && data[pnm->pos] == '\n')
  {
    if(pnm->pos >= len-1)
      return PNM_NEED_DATA;
    else
      pnm->pos++;
  }
  pnm->pos++;
  pnm->state = PNM_READ_RAW;
  return PNM_SUCCESS;
}
