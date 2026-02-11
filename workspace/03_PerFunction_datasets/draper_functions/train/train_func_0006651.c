Amd7930_ph_command(struct IsdnCardState *cs, u_char command, char *s)
{
	if (cs->debug & L1_DEB_ISAC)
		debugl1(cs, "AMD7930: %s: ph_command 0x%02X", s, command);

	cs->dc.amd7930.lmr1 = command;
	wByteAMD(cs, 0xA3, command);
}
