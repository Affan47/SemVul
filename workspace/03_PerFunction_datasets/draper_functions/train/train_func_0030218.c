INTREQ_0 (uae_u16 v)
{
#if 0
	if (!(v & 0x8000) && (v & (0x80 | 0x100 | 0x200 | 0x400) != 0x0780))
		write_log (_T("audirq clear %04x %04x\n"), v, intreq);
#endif

	uae_u16 old = intreq;
	setclr (&intreq, v);

	if (use_eventmode (v)) {

		if (old == intreq && intreq_internal == intreq)
			return;
		event2_newevent_xx (-1, INT_PROCESSING_DELAY, intreq, send_intreq_do);
	} else {
		intreq_internal = intreq;
		if (intreq == old)
			return;
		if (v & 0x8000)
			doint ();
	}
}
