z80pio_d_r( int which , int ch )
{
	z80pio *pio = pios + which;
	if( ch ) ch = 1;

	switch( pio->mode[ch] ){
	case PIO_MODE0:
		return pio->out[ch];
	case PIO_MODE1:
		z80pio_set_rdy(pio, ch, 1);
		z80pio_check_irq( pio , ch );
		return pio->in[ch];
	case PIO_MODE2:
		if( ch ) logerror("PIO-B mode 2 \n");
		z80pio_set_rdy(pio, 1, 1);
		z80pio_check_irq( pio , ch );
		return pio->in[ch];
	case PIO_MODE3:
		return (pio->in[ch]&pio->dir[ch])|(pio->out[ch]&~pio->dir[ch]);
	}
	logerror("PIO-%c data read,bad mode\n",'A'+ch );
	return 0;
}
