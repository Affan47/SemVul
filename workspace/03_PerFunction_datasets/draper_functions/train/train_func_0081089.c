do_stat (const char *path)
{
  int r;
  guestfs_int_stat *ret;
  struct stat statbuf;

  CHROOT_IN;
  r = stat (path, &statbuf);
  CHROOT_OUT;

  if (r == -1) {
    reply_with_perror ("%s", path);
    return NULL;
  }

  ret = malloc (sizeof *ret);
  if (ret == NULL) {
    reply_with_perror ("malloc");
    return NULL;
  }

  ret->dev = statbuf.st_dev;
  ret->ino = statbuf.st_ino;
  ret->mode = statbuf.st_mode;
  ret->nlink = statbuf.st_nlink;
  ret->uid = statbuf.st_uid;
  ret->gid = statbuf.st_gid;
  ret->rdev = statbuf.st_rdev;
  ret->size = statbuf.st_size;
#ifdef HAVE_STRUCT_STAT_ST_BLKSIZE
  ret->blksize = statbuf.st_blksize;
#else
  ret->blksize = -1;
#endif
#ifdef HAVE_STRUCT_STAT_ST_BLOCKS
  ret->blocks = statbuf.st_blocks;
#else
  ret->blocks = -1;
#endif
  ret->atime = statbuf.st_atime;
  ret->mtime = statbuf.st_mtime;
  ret->ctime = statbuf.st_ctime;

  return ret;
}
