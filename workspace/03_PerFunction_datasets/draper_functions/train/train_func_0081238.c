gl846_init_gpio (Genesys_Device * dev)
{
  SANE_Status status = SANE_STATUS_GOOD;
  int idx=0;

  DBGSTART;


  while(gpios[idx].sensor_id!=0 && dev->model->gpo_type!=gpios[idx].sensor_id)
    {
      idx++;
    }
  if(gpios[idx].sensor_id==0)
    {
      DBG (DBG_error, "%s: failed to find GPIO profile for sensor_id=%d\n", __FUNCTION__, dev->model->ccd_type);
      return SANE_STATUS_INVAL;
    }

  RIE (sanei_genesys_write_register (dev, REGA7, gpios[idx].ra7));
  RIE (sanei_genesys_write_register (dev, REGA6, gpios[idx].ra6));

  RIE (sanei_genesys_write_register (dev, REG6B, gpios[idx].r6b));
  RIE (sanei_genesys_write_register (dev, REG6C, gpios[idx].r6c));
  RIE (sanei_genesys_write_register (dev, REG6D, gpios[idx].r6d));
  RIE (sanei_genesys_write_register (dev, REG6E, gpios[idx].r6e));
  RIE (sanei_genesys_write_register (dev, REG6F, gpios[idx].r6f));

  RIE (sanei_genesys_write_register (dev, REGA8, gpios[idx].ra8));
  RIE (sanei_genesys_write_register (dev, REGA9, gpios[idx].ra9));

  DBGCOMPLETED;
  return status;
}
