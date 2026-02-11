iso9660_read (char *buf, int len)
{
  int sector, blkoffset, size, ret;

  if (INODE->file_start == 0)
    return 0;

  ret = 0;
  blkoffset = filepos & (ISO_SECTOR_SIZE - 1);
  sector = filepos >> ISO_SECTOR_BITS;
  while (len > 0)
    {
      size = ISO_SECTOR_SIZE - blkoffset;
      if (size > len)
        size = len;

      disk_read_func = disk_read_hook;

      if (!iso9660_devread(INODE->file_start + sector, blkoffset, size, buf))
	return 0;

      disk_read_func = NULL;

      len -= size;
      buf += size;
      ret += size;
      filepos += size;
      sector++;
      blkoffset = 0;
    }

  return ret;
}
