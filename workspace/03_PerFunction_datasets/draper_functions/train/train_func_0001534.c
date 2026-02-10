rosGetColLbls( void )
{
  static  wxString  osColLbls;
  CmdNgSpicePR  oCmdPR;
  wxString      osNodePair;
  size_t        sz1, sz2;


  oCmdPR = m_oCmdPR;


  if( !m_oCmdPR.m_osaCpnts.IsEmpty( ) && !NetList::m_oaCpnts.IsEmpty( ) )
  {

    for( sz1=0; sz1<oCmdPR.m_osaCpnts.GetCount( ); sz1++ )
    {

      osNodePair = oCmdPR.m_osaCpnts.Item( sz1 );


      for( sz2=0; sz2<NetList::m_oaCpnts.GetCount( ); sz2++ )
      {
        Component & roCpnt1 = NetList::m_oaCpnts.Item( sz2 );

        if( roCpnt1.m_osaNodes.GetCount( ) != 2 ) continue;


        if( roCpnt1.rosGetNodes( ) == osNodePair )
        {
          oCmdPR.m_osaCpnts.Item( sz1 ) = roCpnt1.m_osName;
          break;
        }
      }
    }
  }


  oCmdPR.bFormat( );
  osColLbls = oCmdPR   .AfterFirst( wxT(' ') );
  osColLbls = osColLbls.AfterFirst( wxT(' ') );

  return( osColLbls );
}
