lf_find_xbm_token(
  xbmState *xbm,
  byte *data,
  int len,
  byte **token_start_return,
  int *token_len_return)
{
  int oldpos=xbm->pos;
  int i;
  while (xbm->pos < len && data[xbm->pos] != ' ' && data[xbm->pos] != '\t' &&
         data[xbm->pos] != '\n' && data[xbm->pos] != '\r')
    xbm->pos++;
  if(xbm->pos >= len) return true;
  if(data[xbm->pos] == '\n' || data[xbm->pos] == '\r') return true;
  for(i = xbm->pos - 2; i >= oldpos; i--)
    if(data[i] == '_') break;
  if(i < oldpos) return true;
  *token_start_return = data + i + 1;
  *token_len_return = xbm->pos - i - 1;
  return false;
}
