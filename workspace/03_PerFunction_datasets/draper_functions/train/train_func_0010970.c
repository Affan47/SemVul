InitSwpUnits( void )
{
  wxString    os1;
  eUnitsType  eUnits;


  os1 = m_oChoSrcName.GetStringSelection( );

  eUnits = Component::eGetUnitsType( os1 );

  switch( eUnits )
  {
    case eUNITS_VOLT :
      os1 = wxT("Voltage");
      break;

    case eUNITS_CURR :
      os1 = wxT("Current");
      break;

    case eUNITS_CAP  :
      os1 = wxT("Capacitance");
      break;

    case eUNITS_IND  :
      os1 = wxT("Inductance");
      break;

    case eUNITS_RES  :
      os1 = wxT("Resistance");
      break;

    default          :
      os1 = wxT("Value");
  }


  m_oPnlStart.bSetName( wxString( wxT("Start ") ) + os1 );
  m_oPnlStop .bSetName( wxString( wxT("Stop ")  ) + os1 );
  m_oPnlStart.bSetUnitsType( eUnits );
  m_oPnlStop .bSetUnitsType( eUnits );
  m_oPnlStep .bSetUnitsType( eUnits );
}
