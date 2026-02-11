bSetArgLst( const wxString & rosArgLst )
{
  if( rosArgLst.IsEmpty( ) ) return( FALSE );

  m_osArgLst = rosArgLst;

  return( TRUE );
}
