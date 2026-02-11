create(int ram_top, unsigned int eeprom_size)
{
  EEPROM_PIR *e;

  create_iopin_map();

  _14bit_processor::create();

  e = new EEPROM_PIR(this,pir1);
  e->initialize(eeprom_size);

  e->set_intcon(&intcon_reg);


  set_eeprom_pir(e);

  P16X6X_processor::create_sfr_map();

  status->rp_mask = 0x60;
  indf->base_address_mask1 = 0x80;
  indf->base_address_mask2 = 0x1ff;

  P16F62x::create_sfr_map();


}
