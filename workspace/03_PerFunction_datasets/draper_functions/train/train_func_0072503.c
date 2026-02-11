gl124_init_regs_for_warmup (Genesys_Device * dev,
			    Genesys_Register_Set * reg,
			    int *channels, int *total_size)
{
  int num_pixels;
  SANE_Status status = SANE_STATUS_GOOD;
  Genesys_Register_Set *r;

  DBGSTART;
  if (dev == NULL || reg == NULL || channels == NULL || total_size == NULL)
    return SANE_STATUS_INVAL;

  *channels=3;

  memcpy (reg, dev->reg, (GENESYS_GL124_MAX_REGS + 1) * sizeof (Genesys_Register_Set));
  status = gl124_init_scan_regs (dev,
				 reg,
				 dev->sensor.optical_res,
				 dev->motor.base_ydpi,
				 dev->sensor.sensor_pixels/4,
				 0,
				 dev->sensor.sensor_pixels/2,
				 1,
				 8,
				 *channels,
				 dev->settings.color_filter,
				 SCAN_FLAG_DISABLE_SHADING |
				 SCAN_FLAG_DISABLE_GAMMA |
				 SCAN_FLAG_SINGLE_LINE |
				 SCAN_FLAG_IGNORE_LINE_DISTANCE);

  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "gl124_init_regs_for_warmup: failed to setup scan: %s\n",
	   sane_strstatus (status));
      return status;
    }

  num_pixels = dev->current_setup.pixels;

  *total_size = num_pixels * 3 * 1;

  r = sanei_genesys_get_address (reg, REG02);
  r->value &= ~REG02_MTRPWR;
  RIE (gl124_bulk_write_register (dev, reg, GENESYS_GL124_MAX_REGS));

  DBGCOMPLETED;
  return SANE_STATUS_GOOD;
}
