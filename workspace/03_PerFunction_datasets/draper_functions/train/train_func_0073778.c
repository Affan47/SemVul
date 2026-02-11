pokey_timer_expire(int param)
{
	int chip = param >> 3;
	int timers = param & 7;
	struct POKEYregisters *p = &pokey[chip];

	LOG_TIMER(("POKEY #%d timer %d with IRQEN $%02x\n", chip, param, p->IRQEN));


	timers &= p->IRQEN;

    if( timers )
    {

		p->IRQST |= timers;

		if( p->interrupt_cb )
			(*p->interrupt_cb)(timers);
    }
}
