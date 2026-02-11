mmc_get_blocksize ( CdIo_t *p_cdio)
{
  int i_status;

  uint8_t buf[255] = { 0, };
  uint8_t *p;


  i_status = mmc_mode_sense_6(p_cdio, buf, sizeof(buf),
                              CDIO_MMC_R_W_ERROR_PAGE);

  if (DRIVER_OP_SUCCESS == i_status && buf[3]>=8) {
    p = &buf[4+5];
    return CDIO_MMC_GET_LEN16(p);
  }


  i_status = mmc_mode_sense_10(p_cdio, buf, sizeof(buf),
                               CDIO_MMC_R_W_ERROR_PAGE);
  p = &buf[6];
  if (DRIVER_OP_SUCCESS == i_status && CDIO_MMC_GET_LEN16(p)>=8) {
    return CDIO_MMC_GET_LEN16(p);
  }

#ifdef IS_THIS_CORRECT

  {
    lba_t    lba = 0;
    uint16_t i_blocksize;

    i_status = mmc_read_capacity(p_cdio, &lba, &i_blocksize);
    if ( DRIVER_OP_SUCCESS == i_status )
      return i_blocksize;
#endif

  return DRIVER_OP_UNSUPPORTED;
}
