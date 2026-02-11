mp750_get_status (pixma_t * s, pixma_device_status_t * status)
{
  int error;

  error = query_status (s);
  if (error < 0)
    return error;
  status->hardware = PIXMA_HARDWARE_OK;
  status->adf = (has_paper (s)) ? PIXMA_ADF_OK : PIXMA_ADF_NO_PAPER;
  status->cal =
    (is_calibrated (s)) ? PIXMA_CALIBRATION_OK : PIXMA_CALIBRATION_OFF;
  status->lamp = (is_warming_up (s)) ? PIXMA_LAMP_WARMING_UP : PIXMA_LAMP_OK;
  return 0;
}
