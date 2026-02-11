bProcSchems( int * piArg )
{
  wxFileName  ofn1;
  int         i1;


  if( *piArg >= m_iArgC ) return( FALSE );


  if( m_osGuileProc.IsEmpty( ) )
  {
    for( i1=*piArg; i1<m_iArgC; i1++ )
    {
      ofn1 = wxString( m_ppsArgV[ i1 ], *wxConvCurrent );

      if( ofn1.GetExt( ).Upper( ) != wxT("SCH") ) return( FALSE );
    }
  }


  while( *piArg < m_iArgC )
  {
    ofn1 = wxString( m_ppsArgV[ *piArg ], *wxConvCurrent );

    if( ofn1.IsRelative( ) ) ofn1.MakeAbsolute( );

    m_osaSchemFiles.Add( ofn1.GetFullPath( ) );

    ( *piArg )++;
  }

  return( TRUE );
}
