velocity_reset ( struct velocity_nic *vlc ) {
	int timeout = VELOCITY_TIMEOUT_US;
	uint8_t tmp;

	DBGC ( vlc, "VELOCITY %p reset\n", vlc );


	tmp = readb ( vlc->regs + VELOCITY_STICKY );
	tmp &= ~( VELOCITY_STICKY_DS0 | VELOCITY_STICKY_DS1 );
	writeb ( tmp, vlc->regs + VELOCITY_STICKY );


	tmp = readb ( vlc->regs + VELOCITY_CFGA );
	tmp &= ~VELOCITY_CFGA_PACPI;
	writeb ( tmp, vlc->regs + VELOCITY_CFGA );

	velocity_setbit ( vlc->regs + VELOCITY_CRS1, VELOCITY_CR1_SFRST );


	while ( timeout-- ) {
		udelay ( 1 );
		if ( ( readb ( vlc->regs + VELOCITY_CRS1 ) &
		       VELOCITY_CR1_SFRST ) == 0 )
			return 0;
	}

	return -EINVAL;
}
