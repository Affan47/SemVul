iso9660_ifs_readdir (iso9660_t *p_iso, const char psz_path[])
{
  iso9660_stat_t *p_stat;

  if (!p_iso)    return NULL;
  if (!psz_path) return NULL;

  p_stat = iso9660_ifs_stat (p_iso, psz_path);
  if (!p_stat)   return NULL;

  if (p_stat->type != _STAT_DIR) {
    free(p_stat->rr.psz_symlink);
    free(p_stat);
    return NULL;
  }

  {
    long int ret;
    unsigned offset = 0;
    uint8_t *_dirbuf = NULL;
    CdioList_t *retval = _cdio_list_new ();

    if (p_stat->size != ISO_BLOCKSIZE * p_stat->secsize)
      {
	cdio_warn ("bad size for ISO9660 directory (%ud) should be (%lu)!",
		   (unsigned int) p_stat->size,
		   (unsigned long int) ISO_BLOCKSIZE * p_stat->secsize);
      }

    _dirbuf = calloc(1, p_stat->secsize * ISO_BLOCKSIZE);
    if (!_dirbuf)
      {
        cdio_warn("Couldn't calloc(1, %d)", p_stat->secsize * ISO_BLOCKSIZE);
        return NULL;
      }

    ret = iso9660_iso_seek_read (p_iso, _dirbuf, p_stat->lsn, p_stat->secsize);
    if (ret != ISO_BLOCKSIZE*p_stat->secsize) return NULL;

    while (offset < (p_stat->secsize * ISO_BLOCKSIZE))
      {
	iso9660_dir_t *p_iso9660_dir = (void *) &_dirbuf[offset];
	iso9660_stat_t *p_iso9660_stat;

	if (!iso9660_get_dir_len(p_iso9660_dir))
	  {
	    offset++;
	    continue;
	  }

	p_iso9660_stat = _iso9660_dir_to_statbuf(p_iso9660_dir, p_iso->b_xa,
						 p_iso->i_joliet_level);

	if (p_iso9660_stat)
	  _cdio_list_append (retval, p_iso9660_stat);

	offset += iso9660_get_dir_len(p_iso9660_dir);
      }

    free (_dirbuf);

    if (offset != (p_stat->secsize * ISO_BLOCKSIZE)) {
      free (p_stat);
      _cdio_list_free (retval, true);
      return NULL;
    }

    free (p_stat);
    return retval;
  }
}
