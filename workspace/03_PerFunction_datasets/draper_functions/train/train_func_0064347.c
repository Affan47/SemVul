gl124_feed (Genesys_Device * dev, unsigned int steps)
{
  Genesys_Register_Set local_reg[GENESYS_GL124_MAX_REGS];
  SANE_Status status;
  Genesys_Register_Set *r;
  float resolution;
  uint8_t val;

  DBGSTART;
  DBG (DBG_io, "%s: steps=%d\n", __FUNCTION__, steps);


  memcpy (local_reg, dev->reg, GENESYS_GL124_MAX_REGS * sizeof (Genesys_Register_Set));

  resolution=sanei_genesys_get_lowest_ydpi(dev);
  status = gl124_init_scan_regs (dev,
                                 local_reg,
                                 resolution,
                                 resolution,
                                 0,
                                 steps,
                                 100,
                                 3,
                                 8,
                                 3,
                                 dev->settings.scan_method,
                                 SCAN_MODE_COLOR,
                                 dev->settings.color_filter,
                                 SCAN_FLAG_DISABLE_SHADING |
                                 SCAN_FLAG_DISABLE_GAMMA |
                                 SCAN_FLAG_FEEDING |
                                 SCAN_FLAG_DISABLE_BUFFER_FULL_MOVE |
                                 SCAN_FLAG_IGNORE_LINE_DISTANCE);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
           "gl124_feed: failed to set up registers: %s\n",
           sane_strstatus (status));
      DBGCOMPLETED;
      return status;
    }


  sanei_genesys_set_triple(local_reg,REG_EXPR,0);
  sanei_genesys_set_triple(local_reg,REG_EXPG,0);
  sanei_genesys_set_triple(local_reg,REG_EXPB,0);


  RIE (sanei_genesys_write_register (dev, REG0D, REG0D_CLRLNCNT));
  RIE (sanei_genesys_write_register (dev, REG0D, REG0D_CLRMCNT));


  r = sanei_genesys_get_address (local_reg, REG01);
  r->value &= ~REG01_SCAN;


  RIE (dev->model->cmd_set->bulk_write_register (dev, local_reg, GENESYS_GL124_MAX_REGS));

  status = gl124_start_action (dev);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error, "%s: failed to start motor: %s\n", __FUNCTION__, sane_strstatus (status));
      gl124_stop_action (dev);


      dev->model->cmd_set->bulk_write_register (dev, dev->reg, GENESYS_GL124_MAX_REGS);
      return status;
    }


  do
    {
          status = sanei_genesys_get_status (dev, &val);
    }
  while (status == SANE_STATUS_GOOD && !(val & FEEDFSH));


  RIE(gl124_stop_action (dev));

  DBGCOMPLETED;
  return SANE_STATUS_GOOD;
}
