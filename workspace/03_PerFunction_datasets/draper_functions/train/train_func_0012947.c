gl841_set_lamp_power (Genesys_Device * dev,
		      Genesys_Register_Set * regs, SANE_Bool set)
{
  Genesys_Register_Set * r;
  int i;

  if (set)
    {
      sanei_genesys_set_reg_from_set (regs, 0x03,
				      sanei_genesys_read_reg_from_set (regs,
								       0x03) |
				      REG03_LAMPPWR);

      r = sanei_genesys_get_address (regs, 0x10);
      for (i = 0; i < 6; i++, r++) {
	if (dev->sensor.regs_0x10_0x1d[i] == 0x00)
	  r->value = 0x01;
	else
	  r->value = dev->sensor.regs_0x10_0x1d[i];
      }
      r = sanei_genesys_get_address (regs, 0x19);
      r->value = 0x50;
    }
  else
    {
      sanei_genesys_set_reg_from_set (regs, 0x03,
				      sanei_genesys_read_reg_from_set (regs,
								       0x03) &
				      ~REG03_LAMPPWR);

      r = sanei_genesys_get_address (regs, 0x10);
      for (i = 0; i < 6; i++, r++) {
	r->value = 0x01;
      }
      r = sanei_genesys_get_address (regs, 0x19);
      r->value = 0xff;
    }
}
