process_buffer(float *buf, unsigned int len)
{
  int i;

  for (i = 0; i <  NUMDEMOD; i++)
    if (MASK_ISSET(i) && dem[i]->demod)
      dem[i]->demod(dem_st+i, buf, len);
}
