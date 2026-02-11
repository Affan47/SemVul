gigaset_baud_rate(struct cardstate *cs, unsigned cflag)
{
	u16 val;
	u32 rate;

	cflag &= CBAUD;

	switch (cflag) {
	case    B300: rate =     300; break;
	case    B600: rate =     600; break;
	case   B1200: rate =    1200; break;
	case   B2400: rate =    2400; break;
	case   B4800: rate =    4800; break;
	case   B9600: rate =    9600; break;
	case  B19200: rate =   19200; break;
	case  B38400: rate =   38400; break;
	case  B57600: rate =   57600; break;
	case B115200: rate =  115200; break;
	default:
		rate =  9600;
		dev_err(cs->dev, "unsupported baudrate request 0x%x,"
			" using default of B9600\n", cflag);
	}

	val = 0x383fff / rate + 1;

	return set_value(cs, 1, val);
}
