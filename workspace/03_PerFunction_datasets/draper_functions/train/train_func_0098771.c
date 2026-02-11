mmc_get_drive_cap_buf(const uint8_t *p,
                       cdio_drive_read_cap_t  *p_read_cap,
                       cdio_drive_write_cap_t *p_write_cap,
                       cdio_drive_misc_cap_t  *p_misc_cap)
{

  if (p[2] & 0x01) *p_read_cap  |= CDIO_DRIVE_CAP_READ_CD_R;
  if (p[2] & 0x02) *p_read_cap  |= CDIO_DRIVE_CAP_READ_CD_RW;
  if (p[2] & 0x08) *p_read_cap  |= CDIO_DRIVE_CAP_READ_DVD_ROM;
  if (p[4] & 0x01) *p_read_cap  |= CDIO_DRIVE_CAP_READ_AUDIO;
  if (p[4] & 0x10) *p_read_cap  |= CDIO_DRIVE_CAP_READ_MODE2_FORM1;
  if (p[4] & 0x20) *p_read_cap  |= CDIO_DRIVE_CAP_READ_MODE2_FORM2;
  if (p[5] & 0x01) *p_read_cap  |= CDIO_DRIVE_CAP_READ_CD_DA;
  if (p[5] & 0x10) *p_read_cap  |= CDIO_DRIVE_CAP_READ_C2_ERRS;
  if (p[5] & 0x20) *p_read_cap  |= CDIO_DRIVE_CAP_READ_ISRC;
  if (p[5] & 0x40) *p_read_cap  |= CDIO_DRIVE_CAP_READ_MCN;


  if (p[3] & 0x01) *p_write_cap |= CDIO_DRIVE_CAP_WRITE_CD_R;
  if (p[3] & 0x02) *p_write_cap |= CDIO_DRIVE_CAP_WRITE_CD_RW;
  if (p[3] & 0x10) *p_write_cap |= CDIO_DRIVE_CAP_WRITE_DVD_R;
  if (p[3] & 0x20) *p_write_cap |= CDIO_DRIVE_CAP_WRITE_DVD_RAM;
  if (p[4] & 0x80) *p_misc_cap  |= CDIO_DRIVE_CAP_WRITE_BURN_PROOF;


  if (p[4] & 0x40) *p_misc_cap  |= CDIO_DRIVE_CAP_MISC_MULTI_SESSION;
  if (p[6] & 0x01) *p_misc_cap  |= CDIO_DRIVE_CAP_MISC_LOCK;
  if (p[6] & 0x08) *p_misc_cap  |= CDIO_DRIVE_CAP_MISC_EJECT;
  if (p[6] >> 5 != 0)
    *p_misc_cap |= CDIO_DRIVE_CAP_MISC_CLOSE_TRAY;
}
