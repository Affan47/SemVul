loader_dir_read_sector(libdisk_prop_t *prop, unsigned char *buf, int len)
{
  int h, c, s;
  dir_data_t *data;

  if (prop == NULL)
    return -1;

  if (prop->data == NULL)
    return -1;

  h = prop->head;
  c = prop->cylinder;
  s = prop->sector;
  data = (dir_data_t *)prop->data;

  if (is_system_sector(data->dpb, c, h, s))
    {
      int block = CHS_TO_SECT(data->dpb, c, h, s);
      return read_system_block(data->path, buf, block, len);
    }

  if (is_directory_sector(data->dpb, c, h, s))
    {
      int block = CHS_TO_SECT(data->dpb, c - data->dpb->ofs, h, s);
      memcpy(buf, &data->dir[block * len], len);
      return len;
    }


  int idx = find_index(data, c, h, s);
  if (idx < 0)
    {
      printf("*** allocation unit not found for sector C/H/S %d/%d/%d ***\n", c, h, s);


      return len;
    }

  int au_ofs = AU_TO_OFFSET(data->dpb, data->au[idx], c - data->dpb->ofs, h, s);
  return read_block(data, buf, idx, len * au_ofs, len);
}
