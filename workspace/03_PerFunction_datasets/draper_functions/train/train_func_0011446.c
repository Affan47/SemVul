cdio_init(void)
{

  CdIo_driver_t *all_dp;
  CdIo_driver_t *dp = CdIo_driver;
  const driver_id_t *driver_id_p;

  if (CdIo_last_driver != CDIO_DRIVER_UNINIT) {
    cdio_warn ("Init routine called more than once.");
    return false;
  }

  for (driver_id_p=cdio_drivers; *driver_id_p!=DRIVER_UNKNOWN; driver_id_p++) {
    all_dp = &CdIo_all_drivers[*driver_id_p];
    if ((*CdIo_all_drivers[*driver_id_p].have_driver)()) {
      *dp++ = *all_dp;
      CdIo_last_driver++;
    }
  }

  return true;
}
