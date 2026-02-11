ffs_mount (void)
{
  int retval = 1;

  if ((((current_drive & 0x80) || (current_slice != 0))
       && ! IS_PC_SLICE_TYPE_BSD_WITH_FS (current_slice, FS_BSDFFS))
      || part_length < (SBLOCK + (SBSIZE / DEV_BSIZE))
      || !devread (SBLOCK, 0, SBSIZE, (char *) SUPERBLOCK)
      || SUPERBLOCK->fs_magic != FS_MAGIC)
    retval = 0;

  mapblock = -1;
  mapblock_offset = -1;

  return retval;
}
