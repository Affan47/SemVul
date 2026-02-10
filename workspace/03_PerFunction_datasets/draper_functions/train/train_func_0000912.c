CreateInitC( void )
{
  wxPanel * poPnl;

  if( bIsCreated( eCTLGRP_INITC ) ) return;


  poPnl = (wxPanel *) m_oPnlStart.GetParent( );
  wxString  osInitC[ 3 ] = { wxT("Warm "), wxT("Use ICs"), wxT("Cold ") };
  m_oRbxInitC.Create( poPnl, ID_UNUSED, wxT(" Initial Conditions "),
                      wxPoint( 13, 123 ), wxDefaultSize, 3, osInitC, 3 );
  m_oRbxInitC.SetSelection( eINITC_WARM );
}
