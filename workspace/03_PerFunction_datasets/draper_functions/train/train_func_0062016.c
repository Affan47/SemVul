timer2_running ( void ) {
	return ((inb(PPC_PORTB) & PPCB_T2OUT) == 0);
}
