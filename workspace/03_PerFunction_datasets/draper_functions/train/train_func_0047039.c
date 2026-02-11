Convert2Nodes( wxArrayString & rosaCpnts, SimnNgSpice & roSimn )
{
  Component  tCpnt;
  wxString   os1;
  size_t     sz1;

  for( sz1=0; sz1<rosaCpnts.GetCount( ); sz1++ )
  {
    os1 = rosaCpnts.Item( sz1 );
    tCpnt = roSimn.roGetCpnt( os1 );
    if( ! tCpnt.bParse( ) )                 continue;
    if( tCpnt.m_osaNodes.GetCount( ) != 2 ) continue;
    os1.Empty( );
    os1 << tCpnt.m_osaNodes.Item( 0 ) << wxT(',') << tCpnt.m_osaNodes.Item( 1 );
    rosaCpnts.Item( sz1 ) = os1;
  }
}
