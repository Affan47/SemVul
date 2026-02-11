libdisk_seek(libdisk_prop_t **prop, int head, int cylinder, int sector)
{
  libdisk_prop_t *p;

  if (prop == NULL)
    return -1;

  p = (*prop);
  p->head = head;
  p->cylinder = cylinder;
  p->sector = sector;

  return 0;
}
