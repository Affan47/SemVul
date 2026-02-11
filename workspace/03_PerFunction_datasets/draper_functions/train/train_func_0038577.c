get_disc_last_lsn_linux (void *p_user_data)
{
  _img_private_t *p_env = p_user_data;

  struct cdrom_tocentry tocent;
  uint32_t i_size;

  if (!p_env->gen.toc_init) read_toc_linux (p_user_data) ;

  tocent.cdte_track = CDIO_CDROM_LEADOUT_TRACK;
  tocent.cdte_format = CDROM_LBA;
  if (ioctl (p_env->gen.fd, CDROMREADTOCENTRY, &tocent) == -1)
    {
      cdio_warn ("ioctl CDROMREADTOCENTRY failed: %s\n", strerror(errno));
      return CDIO_INVALID_LSN;
    }

  i_size = tocent.cdte_addr.lba;

  return i_size;
}
