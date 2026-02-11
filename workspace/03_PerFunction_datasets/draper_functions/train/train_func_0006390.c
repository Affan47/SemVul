z80pio_interrupt_check( z80pio *pio )
{
	int state;

	if( pio->int_state[1] & Z80_INT_IEO ) state  = Z80_INT_IEO;
	else                                  state  = pio->int_state[1];
	if( pio->int_state[0] & Z80_INT_IEO ) state  = Z80_INT_IEO;
	else                                  state |= pio->int_state[0];

	if (pio->intr) (*pio->intr)(state);
}
