iso9660_get_posix_filemode(const iso9660_stat_t *p_iso_dirent)
{
  mode_t mode = 0;

#ifdef HAVE_ROCK
  if (yep == p_iso_dirent->rr.b3_rock) {
      return iso9660_get_posix_filemode_from_rock(&p_iso_dirent->rr);
  } else
#endif
  if (p_iso_dirent->b_xa) {
    return iso9660_get_posix_filemode_from_xa(p_iso_dirent->xa.attributes);
  }
  return mode;
}
