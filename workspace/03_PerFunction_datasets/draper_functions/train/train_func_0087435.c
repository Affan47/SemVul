PrintControlRegister(const char *devicename, uae_u8 value)
{
	DUNUSED(devicename);

	switch(value & ACIA_CR_PREDIV_MASK) {
		case ACIA_CR_PREDIV1:
			D(bug("%s: clock = 500 kHz", devicename));
			break;
		case ACIA_CR_PREDIV16:
			D(bug("%s: clock = 31250 Hz", devicename));
			break;
		case ACIA_CR_PREDIV64:
			D(bug("%s: clock = 7812.5 Hz", devicename));
			break;
		case ACIA_CR_RESET:
		default:
			break;
	}


	if (value & (1<<ACIA_CR_PARITY)) {
		D(bug("%s: parity off", devicename));
	} else {
		D(bug("%s: parity on", devicename));
	}
	if (value & (1<<ACIA_CR_STOPBITS)) {
		D(bug("%s: 1 stop bit", devicename));
	} else {
		D(bug("%s: 2 stop bits", devicename));
	}
	if (value & (1<<ACIA_CR_DATABITS)) {
		D(bug("%s: 8 data bits", devicename));
	} else {
		D(bug("%s: 7 data bits", devicename));
	}


	if (value & (1<<ACIA_CR_EMIT_INTER)) {
		D(bug("%s: emit interrupt enabled", devicename));
	} else {
		D(bug("%s: emit interrupt disabled", devicename));
	}
	if (value & (1<<ACIA_CR_EMIT_RTS)) {
		D(bug("%s: RTS high", devicename));
	} else {
		D(bug("%s: RTS low", devicename));
	}
	if (((value>>ACIA_CR_EMIT_INTER) & 0x03)==0x03) {
		D(bug("%s: emit BREAK", devicename));
	}


	if (value & (1<<ACIA_CR_REC_INTER)) {
		D(bug("%s: receive interrupt enabled", devicename));
	} else {
		D(bug("%s: receive interrupt disabled", devicename));
	}
}
