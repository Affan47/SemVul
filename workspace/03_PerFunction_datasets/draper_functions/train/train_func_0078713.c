mdec1_read( UINT32 n_address, INT32 n_size )
{
	if( ( m_n_mdec0_command & ( 1L << 29 ) ) != 0 )
	{
		while( n_size > 0 )
		{
			m_n_mdec0_address = mdec_unpack( m_n_mdec0_address );
			mdec_yuv2_to_rgb15( n_address );
			n_address += ( 16 * 16 ) * 2;
			n_size -= ( 16 * 16 ) / 2;
		}
	}
	else
	{
		verboselog( 0, "mdec 24bit not supported\n" );
	}
	m_n_mdec1_status &= ~( 1L << 29 );
}
