Print( const wxString & rosPrefix )
{
  cout << rosPrefix .mb_str( ) << "wxString::"
       << this     ->mb_str( ) << '\n';

  cout << rosPrefix .mb_str( ) << "m_osErrMsg : \""
       << m_osErrMsg.mb_str( ) << "\"\n";

  cout << rosPrefix .mb_str( ) << "m_eSimEng  : ";
  switch( m_eSimEng )
  {
    case eSIMR_GNUCAP  : cout << "eSIMR_GNUCAP";  break;
    case eSIMR_NGSPICE : cout << "eSIMR_NGSPICE"; break;
    case eSIMR_NONE    : cout << "eSIMR_NONE";    break;
    default            : cout << "Invalid";       break;
  }
  cout << '\n';

  cout << rosPrefix .mb_str( ) << "m_eCmdType : ";
  switch( m_eCmdType )
  {
    case eCMD_OP   : cout << "eANA_OP";   break;
    case eCMD_DC   : cout << "eANA_DC";   break;
    case eCMD_AC   : cout << "eANA_AC";   break;
    case eCMD_TR   : cout << "eANA_TR";   break;
    case eCMD_FO   : cout << "eANA_FO";   break;
    case eCMD_DI   : cout << "eANA_DI";   break;
    case eCMD_NO   : cout << "eANA_NO";   break;
    case eCMD_PZ   : cout << "eANA_PZ";   break;
    case eCMD_SE   : cout << "eANA_SE";   break;
    case eCMD_TF   : cout << "eANA_TF";   break;

    case eCMD_OPT  : cout << "eCMD_OPT";  break;
    case eCMD_IC   : cout << "eCMD_IC";   break;
    case eCMD_PR   : cout << "eCMD_PR";   break;
    case eCMD_GEN  : cout << "eCMD_GEN";  break;

    case eCMD_NONE : cout << "eANA_NONE"; break;
    default        : cout << "Invalid";   break;
  }
  cout << '\n';
}
