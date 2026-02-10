loader_BASIC_load(const char *filename,
                  unsigned char *data,
                  long size,
                  fileio_prop_t **prop)
{
  int b;
  long xsize, len;
  unsigned char *sptr, *dptr;

  *prop = (fileio_prop_t *)malloc(sizeof(fileio_prop_t));
  if (*prop == NULL)
    return -1;
  memset(*prop, 0, sizeof(fileio_prop_t));

  switch (*data)
    {
    case 0xd3: (*prop)->type = FILEIO_TYPE_BAS; break;
    case 0xd7: (*prop)->type = FILEIO_TYPE_PROT_BAS; break;
    default: return -1;
    }

  xsize = size + (size + 127) / 128;

  (*prop)->valid = FILEIO_V_NONE;
  (*prop)->load_addr = 0;
  (*prop)->start_addr = 0;
  (*prop)->autostart  = 0;
  (*prop)->size = xsize;
  memcpy((*prop)->name, data + 3, 8);
  (*prop)->name[8] = '\0';

  (*prop)->data = (unsigned char *)malloc(xsize);
  if ((*prop)->data == 0)
    return -1;

  sptr = data;
  dptr = (*prop)->data;

  b = 1;
  while (size > 0)
    {
      *dptr++ = b++;
      len = (size > 128) ? 128 : size;
      memcpy(dptr, sptr, len);
      dptr += 128;
      sptr += 128;
      size -= 128;
    }

  return 0;
}
