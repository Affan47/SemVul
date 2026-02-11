create_iopin_map(void)
{
  package = new Package(20);
  if(!package)
    return;

  package->assign_pin(1, 0);

  package->assign_pin( 2, m_porta->addPin(new IO_bi_directional_pu("porta5"),5));
  package->assign_pin( 3, m_porta->addPin(new IO_bi_directional_pu("porta4"),4));
  package->assign_pin( 4, m_porta->addPin(new IOPIN("porta3"),3));
  package->assign_pin( 5, m_portc->addPin(new IO_bi_directional_pu("portc5"),5));
  package->assign_pin( 6, m_portc->addPin(new IO_bi_directional("portc4"),4));
  package->assign_pin( 7, m_portc->addPin(new IO_bi_directional("portc3"),3));

  package->assign_pin( 8, m_portc->addPin(new IO_bi_directional("portc6"),6));
  package->assign_pin( 9, m_portc->addPin(new IO_bi_directional("portc7"),7));
  package->assign_pin(10, m_portb->addPin(new IO_bi_directional("portb7"),7));

  package->assign_pin(11, m_portb->addPin(new IO_bi_directional_pu("portb6"),6));
  package->assign_pin(12, m_portb->addPin(new IO_bi_directional_pu("portb5"),5));
  package->assign_pin(13, m_portb->addPin(new IO_bi_directional_pu("portb4"),4));
  package->assign_pin(14, m_portc->addPin(new IO_bi_directional_pu("portc2"),2));
  package->assign_pin(15, m_portc->addPin(new IO_bi_directional_pu("portc1"),1));
  package->assign_pin(16, m_portc->addPin(new IO_bi_directional_pu("portc0"),0));
  package->assign_pin(17, m_porta->addPin(new IO_bi_directional_pu("porta2"),2));
  package->assign_pin(18, m_porta->addPin(new IO_bi_directional_pu("porta1"),1));
  package->assign_pin(19, m_porta->addPin(new IO_bi_directional_pu("porta0"),0));

  package->assign_pin(20, 0);


  tmr1l.setIOpin(&(*m_portc)[0]);

}
