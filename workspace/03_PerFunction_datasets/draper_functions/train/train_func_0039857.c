create(int ram_top, int eeprom_size)
{

  create_iopin_map();

  e = new EEPROM_EXTND(this, pir2);
  set_eeprom(e);

  pic_processor::create();


  e->initialize(eeprom_size, 16, 16, 0x8000);
  e->set_intcon(intcon);
  e->get_reg_eecon1()->set_valid_bits(0xff);

  add_file_registers(0x20, ram_top, 0x00);
  _14bit_e_processor::create_sfr_map();
  P12F1822::create_sfr_map();

  if (m_configMemory && m_configMemory->getConfigWord(6))
      m_configMemory->getConfigWord(6)->set(0x2700);
}
