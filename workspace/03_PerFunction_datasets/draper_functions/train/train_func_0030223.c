lcdwinamp_HD44780_readkeypad(PrivateData *p, unsigned int YData)
{
	unsigned char readval;


	port_out(p->port, ~YData & 0x00FF);

	if (p->delayBus) p->hd44780_functions->uPause(p, 1);


	readval = ~ port_in(p->port + 1) ^ INMASK;


	return (((readval & FAULT) / FAULT <<4) |
		((readval & SELIN) / SELIN <<3) |
		((readval & PAPEREND) / PAPEREND <<2) |
		((readval & BUSY) / BUSY <<1) |
		((readval & ACK) / ACK )) & ~p->stuckinputs;
}
