send( t_CKBYTE status, t_CKBYTE data1, t_CKBYTE data2 )
{
    if( !m_valid ) return 0;


    m_msg.clear();

    m_msg.push_back( status );
    m_msg.push_back( data1 );
    m_msg.push_back( data2 );

    mout->sendMessage( &m_msg );

    return 3;
}
