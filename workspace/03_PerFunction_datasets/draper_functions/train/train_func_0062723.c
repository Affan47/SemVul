chpho_eq_pho(int idx, phokey_t *phos, int len)
{
  int i;

  for(i=0; i < len; i++)
    if (tss.chpho[idx+i].pho != phos[i])
       return FALSE;

  return TRUE;
}
