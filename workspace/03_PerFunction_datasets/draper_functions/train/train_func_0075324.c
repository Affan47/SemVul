cdio_get_drive_cap (const CdIo_t *p_cdio,
                    cdio_drive_read_cap_t  *p_read_cap,
                    cdio_drive_write_cap_t *p_write_cap,
                    cdio_drive_misc_cap_t  *p_misc_cap)
{

  *p_read_cap  = CDIO_DRIVE_CAP_UNKNOWN;
  *p_write_cap = CDIO_DRIVE_CAP_UNKNOWN;
  *p_misc_cap  = CDIO_DRIVE_CAP_UNKNOWN;

  if (p_cdio && p_cdio->op.get_drive_cap) {
    p_cdio->op.get_drive_cap(p_cdio->env, p_read_cap, p_write_cap, p_misc_cap);
  }
}
