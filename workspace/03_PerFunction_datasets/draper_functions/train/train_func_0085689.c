hfsutil_unmount(hfsvol *vol, int *result)
{
  if (hfs_umount(vol) == -1 && *result == 0)
    {
      hfsutil_perror("Error closing HFS volume");
      *result = 1;
    }
}
