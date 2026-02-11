i2c_HD44780_senddata(PrivateData *p, unsigned char displayID, unsigned char flags, unsigned char ch)
{
	unsigned char enableLines = 0, portControl = 0;
	unsigned char h = (ch >> 4) & 0x0f;
	unsigned char l = ch & 0x0f;

	if (flags == RS_INSTR)
		portControl = 0;
	else
		portControl = RS;

	portControl |= p->backlight_bit;

	enableLines = EN;

	i2c_out(p, portControl | h);
	if (p->delayBus)
		p->hd44780_functions->uPause(p, 1);
	i2c_out(p, enableLines | portControl | h);
	if (p->delayBus)
		p->hd44780_functions->uPause(p, 1);
	i2c_out(p, portControl | h);

	i2c_out(p, portControl | l);
	if (p->delayBus)
		p->hd44780_functions->uPause(p, 1);
	i2c_out(p, enableLines | portControl | l);
	if (p->delayBus)
		p->hd44780_functions->uPause(p, 1);
	i2c_out(p, portControl | l);
}
