gl843_init_gpio (Genesys_Device * dev)
{
  SANE_Status status = SANE_STATUS_GOOD;
  int idx;

  DBGSTART;

  RIE (sanei_genesys_write_register (dev, REG6E, dev->gpo.enable[0]));
  RIE (sanei_genesys_write_register (dev, REG6F, dev->gpo.enable[1]));
  RIE (sanei_genesys_write_register (dev, REG6C, dev->gpo.value[0]));
  RIE (sanei_genesys_write_register (dev, REG6D, dev->gpo.value[1]));

  idx=0;
  while(dev->model->gpo_type != gpios[idx].gpo_type && gpios[idx].gpo_type!=0)
    {
      idx++;
    }
  if (gpios[idx].gpo_type!=0)
    {
      RIE (sanei_genesys_write_register (dev, REGA6, gpios[idx].ra6));
      RIE (sanei_genesys_write_register (dev, REGA7, gpios[idx].ra7));
      RIE (sanei_genesys_write_register (dev, REGA8, gpios[idx].ra8));
      RIE (sanei_genesys_write_register (dev, REGA9, gpios[idx].ra9));
    }
  else
    {
      status=SANE_STATUS_INVAL;
    }

  DBGCOMPLETED;
  return status;
}
