bSetInitMsg( const wxString & rosMsg )
{
  if( rosMsg.Length( ) > 60 ) return( FALSE );

  m_osInitMsg = rosMsg;

  return( TRUE );
}
