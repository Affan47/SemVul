z80ctc_init (z80ctc_interface *intf)
{
	int i;

	memset (ctcs, 0, sizeof (ctcs));

	for (i = 0; i < intf->num; i++)
	{
		ctcs[i].clock = intf->baseclock[i];
		ctcs[i].invclock16 = 16.0 / (double)intf->baseclock[i];
		ctcs[i].invclock256 = 256.0 / (double)intf->baseclock[i];
		ctcs[i].notimer = intf->notimer[i];
		ctcs[i].intr = intf->intr[i];
		ctcs[i].timer[0] = timer_alloc(z80ctc_timercallback);
		ctcs[i].timer[1] = timer_alloc(z80ctc_timercallback);
		ctcs[i].timer[2] = timer_alloc(z80ctc_timercallback);
		ctcs[i].timer[3] = timer_alloc(z80ctc_timercallback);
		ctcs[i].zc[0] = intf->zc0[i];
		ctcs[i].zc[1] = intf->zc1[i];
		ctcs[i].zc[2] = intf->zc2[i];
		ctcs[i].zc[3] = 0;
		z80ctc_reset (i);
	}
}
