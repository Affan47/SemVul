iowlcd_set_text(PrivateData *p, int x, int y, int len, unsigned char *data)
{
  if (iowlcd_set_pos(p, x, y) == IOW_ERROR)
    return IOW_ERROR;
  return iowlcd_write_data(p, len, data);
}
