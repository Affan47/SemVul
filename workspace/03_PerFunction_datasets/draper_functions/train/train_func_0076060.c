bSetCmdLine( int iArgC, wxChar ** ppsArgV )
{

  if( iArgC <= 0 )      return( FALSE );
  if( ppsArgV == NULL ) return( FALSE );

  m_iArgC   = iArgC;
  m_ppsArgV = ppsArgV;

  return( TRUE );
}
