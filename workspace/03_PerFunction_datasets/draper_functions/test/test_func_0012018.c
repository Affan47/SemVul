gl847_begin_scan (Genesys_Device * dev, Genesys_Register_Set * reg,
		  SANE_Bool start_motor)
{
  SANE_Status status;
  uint8_t val;
  Genesys_Register_Set *r;

  DBGSTART;


  if (dev->model->gpo_type != GPO_CANONLIDE700)
    {
      RIE (sanei_genesys_read_register (dev, REG6C, &val));
      val &= ~REG6C_GPIO10;
      RIE (sanei_genesys_write_register (dev, REG6C, val));
    }

  val = REG0D_CLRLNCNT;
  RIE (sanei_genesys_write_register (dev, REG0D, val));
  val = REG0D_CLRMCNT;
  RIE (sanei_genesys_write_register (dev, REG0D, val));

  RIE (sanei_genesys_read_register (dev, REG01, &val));
  val |= REG01_SCAN;
  RIE (sanei_genesys_write_register (dev, REG01, val));
  r = sanei_genesys_get_address (reg, REG01);
  r->value = val;

  if (start_motor)
    {
      RIE (sanei_genesys_write_register (dev, REG0F, 1));
    }
  else
    {
      RIE (sanei_genesys_write_register (dev, REG0F, 0));
    }

  DBGCOMPLETED;

  return status;
}
