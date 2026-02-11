assignMCLRPin(int pkgPinNumber)
{
  if (package)
  {

    if (m_MCLR == NULL)
    {
	m_MCLR_pin = pkgPinNumber;
    	m_MCLR = new IO_open_collector("MCLR");
	m_MCLR_Save = package->get_pin(pkgPinNumber);
    	package->assign_pin(pkgPinNumber,m_MCLR, false);

    	m_MCLRMonitor = new MCLRPinMonitor(this);
    	m_MCLR->setMonitor(m_MCLRMonitor);
    	m_MCLR->newGUIname("MCLR");
    }
    else if (m_MCLR != package->get_pin(pkgPinNumber))
    {

        cout << "BUG?: assigning multiple MCLR pins: "
	<< dec << pkgPinNumber << " " << __FILE__ <<  " "
	<< __LINE__ << endl;
    }
  }
}
