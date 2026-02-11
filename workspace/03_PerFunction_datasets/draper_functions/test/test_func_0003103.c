_ifs_stat_root (iso9660_t *p_iso)
{
  iso9660_stat_t *p_stat;
  iso9660_dir_t *p_iso9660_dir;

#ifdef HAVE_JOLIET
  p_iso9660_dir = p_iso->i_joliet_level
    ? &(p_iso->svd.root_directory_record)
    : &(p_iso->pvd.root_directory_record) ;
#else
  p_iso9660_dir = &(p_iso->pvd.root_directory_record) ;
#endif

  p_stat = _iso9660_dir_to_statbuf (p_iso9660_dir, p_iso->b_xa,
				    p_iso->i_joliet_level);
  return p_stat;
}
