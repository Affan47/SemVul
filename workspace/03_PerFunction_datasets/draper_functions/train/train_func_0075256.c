bParse( void )
{
  wxStringTokenizer  ostk1;
  wxString           os1;
  size_t             szt1;


  os1 = (wxString &) *this;
  bClear( );
  wxString::assign( os1 );
  m_osErrMsg.Empty( );


  if( IsEmpty( ) )               return( bValidate( ) );
  ostk1.SetString( os1 );


  bSetName( ostk1.GetNextToken( ) );


  if( ! ostk1.HasMoreTokens( ) ) return( bValidate( ) );
  bSetNodes( ostk1.GetString( ) );
  for( szt1=0; szt1<m_osaNodes.GetCount( ); szt1++ )
    ostk1.GetNextToken( );


  if( ! ostk1.HasMoreTokens( ) ) return( bValidate( ) );
  bSetValue( ostk1.GetString( ) );

  return( bValidate( ) );
}
