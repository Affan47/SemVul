is_pcx(file_data_t *fd)
{
  if(!fd->data || fd->size < 0x381) return 0;
  if(
    fd->data[0] != 10 ||
    fd->data[1] != 5 ||
    fd->data[2] != 1 ||
    fd->data[3] != 8 ||
    fd->data[fd->size - 0x301] != 12
  ) return 0;

  return 1;
}
