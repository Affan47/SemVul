psx_irq_update( void )
{
	if( ( m_n_irqdata & m_n_irqmask ) != 0 )
	{
		verboselog( 2, "psx irq assert\n" );
		cpu_set_irq_line( 0, 0, ASSERT_LINE );
	}
	else
	{
		verboselog( 2, "psx irq clear\n" );
		cpu_set_irq_line( 0, 0, CLEAR_LINE );
	}
}
