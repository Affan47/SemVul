mdec0_write( UINT32 n_address, INT32 n_size )
{
	int n_index;

	switch( m_n_mdec0_command >> 28 )
	{
	case 0x3:
		verboselog( 1, "mdec decode %08x %08x %08x\n", m_n_mdec0_command, n_address, n_size );
		m_n_mdec0_address = n_address;
		m_n_mdec0_size = n_size;
		m_n_mdec1_status |= ( 1L << 29 );
		break;
	case 0x4:
		verboselog( 1, "mdec quantize table %08x %08x %08x\n", m_n_mdec0_command, n_address, n_size );
		for( n_index = 0; n_index < DCTSIZE2; n_index++ )
		{
			m_p_n_mdec_quantize_y[ n_index ] = psxreadbyte( n_address + n_index );
			m_p_n_mdec_quantize_uv[ n_index ] = psxreadbyte( n_address + n_index + DCTSIZE2 );
		}
		break;
	case 0x6:
		verboselog( 1, "mdec cosine table %08x %08x %08x\n", m_n_mdec0_command, n_address, n_size );
		for( n_index = 0; n_index < DCTSIZE2; n_index++ )
		{
			m_p_n_mdec_cos[ n_index ] = (INT16)psxreadword( n_address + ( n_index * 2 ) );
		}
		mdec_cos_precalc();
		break;
	default:
		verboselog( 0, "mdec unknown command %08x %08x %08x\n", m_n_mdec0_command, n_address, n_size );
		break;
	}
}
