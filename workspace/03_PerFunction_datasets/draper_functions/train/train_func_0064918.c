set_config_word(unsigned int address, unsigned int cfg_word)
{
  enum {
    CFG_FOSC0 = 1<<0,
    CFG_FOSC1 = 1<<1,
    CFG_FOSC2 = 1<<4,
    CFG_MCLRE = 1<<5
  };


  if (pic_processor::set_config_word(address, cfg_word)) {

    if (verbose)
        cout << "p16f628 setting config word 0x" << hex << cfg_word << '\n';


    unsigned int valid_pins = m_porta->getEnableMask();

    set_int_osc(false);

    switch(cfg_word & (CFG_FOSC0 | CFG_FOSC1 | CFG_FOSC2)) {

    case 0:
    case 1:
    case 2:
        (m_porta->getPin(6))->newGUIname("OSC2");
        (m_porta->getPin(7))->newGUIname("OSC1");
        break;

    case 0x13:
        (m_porta->getPin(6))->newGUIname("CLKOUT");
        (m_porta->getPin(7))->newGUIname("OSC1");
        break;

    case 3:
    case 0x12:
        (m_porta->getPin(7))->newGUIname("CLKIN");
        valid_pins =  (valid_pins & 0x7f)|0x40;
        break;

    case 0x10:
	set_int_osc(true);
        (m_porta->getPin(6))->newGUIname("porta6");
        (m_porta->getPin(7))->newGUIname("porta7");
        valid_pins |= 0xc0;
        break;

    case 0x11:
	set_int_osc(true);
	(m_porta->getPin(6))->newGUIname("CLKOUT");
        (m_porta->getPin(7))->newGUIname("porta7");

        valid_pins = (valid_pins & 0xbf)|0x80;
        break;

    }


    if (! (cfg_word & CFG_MCLRE)) {
      unassignMCLRPin();
      valid_pins |= ( 1<< 5);
    }
    else
    {
	assignMCLRPin(4);
    }


    if (valid_pins != m_porta->getEnableMask())
    {
        m_porta->setEnableMask(valid_pins);
        m_porta->setTris(m_trisa);
    }
    return true;
  }

  return false;
}
