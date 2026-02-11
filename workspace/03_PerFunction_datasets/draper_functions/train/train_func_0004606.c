cdio_get_devices_ret ( driver_id_t *p_driver_id)
{
  CdIo_t *p_cdio;

  switch (*p_driver_id) {

  case DRIVER_DEVICE:
    p_cdio = scan_for_driver(cdio_device_drivers, NULL, NULL);
    *p_driver_id = cdio_get_driver_id(p_cdio);
    break;
  case DRIVER_UNKNOWN:
    p_cdio = scan_for_driver(cdio_drivers, NULL, NULL);
    *p_driver_id = cdio_get_driver_id(p_cdio);
    break;
  default:
    return (*CdIo_all_drivers[*p_driver_id].get_devices)();
  }

  if (p_cdio == NULL) return NULL;
  if (p_cdio->op.get_devices) {
    char **devices = p_cdio->op.get_devices ();
    cdio_destroy(p_cdio);
    return devices;
  } else {
    return NULL;
  }
}
