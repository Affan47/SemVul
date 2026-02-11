bCreate( wxWindow * poWin, wxWindowID oWinID, int iWidth )
{
  wxSize  oSize=wxDefaultSize;


  if( bIsCreated( ) )                                       return( TRUE );


  if( iWidth > 0 ) oSize.SetWidth( iWidth );
  if( ! Create( poWin, oWinID, wxDefaultPosition, oSize ) ) return( FALSE );


  if( ! bSetUnitsType( m_eUnitsType ) )                     return( FALSE );
  if( ! bSetUnits( m_osDefUnits ) )                         return( FALSE );

  return( TRUE );
}
