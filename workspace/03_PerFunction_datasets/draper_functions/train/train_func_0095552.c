dma_timer( int n_channel, UINT32 n_scanline )
{
	if( n_scanline != 0xffffffff )
	{
		timer_adjust( m_p_timer_dma[ n_channel ], cpu_getscanlinetime( n_scanline ), n_channel, 0 );
	}
	else
	{
		timer_adjust( m_p_timer_dma[ n_channel ], TIME_NEVER, 0, 0 );
	}
	m_p_n_dma_lastscanline[ n_channel ] = n_scanline;
}
