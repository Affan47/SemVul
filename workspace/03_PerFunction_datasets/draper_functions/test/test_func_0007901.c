setparams (struct devstruct *dev, uaecptr req)
{
	int v;
	int rbuffer, baud, rbits, wbits, sbits, rtscts, parity, xonxoff;

	rbuffer = get_long (req + io_RBufLen);
	v = get_long (req + io_ExtFlags);
	if (v) {
		write_log (_T("UAESER: io_ExtFlags=%08x, not supported\n"), v);
		return 5;
	}
	baud = get_long (req + io_Baud);
	v = get_byte (req + io_SerFlags);
	if (v & SERF_EOFMODE) {
		write_log (_T("UAESER: SERF_EOFMODE not supported\n"));
		return 5;
	}
	xonxoff = (v & SERF_XDISABLED) ? 0 : 1;
	if (xonxoff) {
		xonxoff |= (get_long (req + io_CtlChar) << 8) & 0x00ffff00;
	}
	rtscts = (v & SERF_7WIRE) ? 1 : 0;
	parity = 0;
	if (v & SERF_PARTY_ON)
		parity = (v & SERF_PARTY_ODD) ? 1 : 2;
	rbits = get_byte (req + io_ReadLen);
	wbits = get_byte (req + io_WriteLen);
	sbits = get_byte (req + io_StopBits);
	if ((rbits != 7 && rbits != 8) || (wbits != 7 && wbits != 8) || (sbits != 1 && sbits != 2) || rbits != wbits) {
		write_log (_T("UAESER: Read=%d, Write=%d, Stop=%d, not supported\n"), rbits, wbits, sbits);
		return 5;
	}
	write_log (_T("%s:%d BAUD=%d BUF=%d BITS=%d+%d RTSCTS=%d PAR=%d XO=%06X\n"),
		getdevname(), dev->unit,
		baud, rbuffer, rbits, sbits, rtscts, parity, xonxoff);
	v = uaeser_setparams (dev->sysdata, baud, rbuffer,
		rbits, sbits, rtscts, parity, xonxoff);
	if (v) {
		write_log (_T("->failed\n"));
		return v;
	}
	return 0;
}
