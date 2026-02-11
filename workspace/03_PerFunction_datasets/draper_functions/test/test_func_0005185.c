hfs_closedir(hfsdir *dir)
{
  hfsvol *vol = dir->vol;

  if (dir->prev)
    dir->prev->next = dir->next;
  if (dir->next)
    dir->next->prev = dir->prev;
  if (dir == vol->dirs)
    vol->dirs = dir->next;

  FREE(dir);

  return 0;
}
