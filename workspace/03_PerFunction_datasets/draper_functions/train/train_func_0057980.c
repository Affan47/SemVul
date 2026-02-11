gl843_xpa_lamp_on(Genesys_Device *dev)
{
  uint8_t val;
  SANE_Status status=SANE_STATUS_GOOD;

  DBGSTART;


  RIE(sanei_genesys_read_register(dev, REGA6, &val));


  val &= ~(REGA6_GPIO24|REGA6_GPIO23);


  val |= REGA6_GPIO22 | REGA6_GPIO21 | REGA6_GPIO19;

  RIE(sanei_genesys_write_register(dev, REGA6, val));

  RIE(sanei_genesys_read_register(dev, REGA7, &val));
  val|=REGA7_GPOE24;
  val|=REGA7_GPOE23;
  val|=REGA7_GPOE22;
  RIE(sanei_genesys_write_register(dev, REGA7, val));

  DBGCOMPLETED;
  return status;
}
