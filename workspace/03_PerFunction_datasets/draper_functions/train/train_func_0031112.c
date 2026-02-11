loader_22dsk_read_sector(libdisk_prop_t *prop, unsigned char *buf, int len)
{
  int l;
  dsk_data_t *data;

  if (loader_22dsk_seek(prop) < 0)
    return -1;

  data = (dsk_data_t *)prop->data;

  l = do_read(data, buf, len);

  if (l != len)
    return -1;

  return l;
}
