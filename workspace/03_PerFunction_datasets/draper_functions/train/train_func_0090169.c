osc_mode(unsigned int value)
{
  IOPIN *m_pin;
  unsigned int pin_Number =  get_osc_pin_Number(0);

  set_int_osc(false);
  if (pin_Number < 253)
  {
	m_pin = package->get_pin(pin_Number);
	if (value == 8 || value == 9)
	{
	    clr_clk_pin(pin_Number, get_osc_PinMonitor(0),
		m_porta, m_trisa, m_lata);
	    set_int_osc(true);
	}
	else
	{
	    set_clk_pin(pin_Number, get_osc_PinMonitor(0), "OSC1", true,
		 m_porta, m_trisa, m_lata);
	}
  }
  if ( (pin_Number =  get_osc_pin_Number(1)) < 253 &&
	(m_pin = package->get_pin(pin_Number)))
  {
	pll_factor = 0;
	switch(value)
	{
	case 6:
	    pll_factor = 2;
	case 0:
	case 1:
	case 2:
	    set_clk_pin(pin_Number, get_osc_PinMonitor(1), "OSC2", true,
		m_porta, m_trisa, m_lata);
	    break;

	case 4:
	case 9:
	case 12:
	case 13:
	case 14:
	case 15:
	    cout << "CLKO not simulated\n";
	    set_clk_pin(pin_Number, get_osc_PinMonitor(1) , "CLKO", false,
		m_porta, m_trisa, m_lata);
	    break;

	default:
	    clr_clk_pin(pin_Number, get_osc_PinMonitor(1),
		m_porta, m_trisa, m_lata);
	    break;
	}
  }

}
