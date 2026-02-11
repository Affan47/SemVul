via_hw_init(struct via_ircc_cb *self)
{
	int iobase = self->io.fir_base;

	SetMaxRxPacketSize(iobase, 0x0fff);

	EnRXFIFOReadyInt(iobase, OFF);
	EnRXFIFOHalfLevelInt(iobase, OFF);
	EnTXFIFOHalfLevelInt(iobase, OFF);
	EnTXFIFOUnderrunEOMInt(iobase, ON);
	EnTXFIFOReadyInt(iobase, OFF);
	InvertTX(iobase, OFF);
	InvertRX(iobase, OFF);

	if (ReadLPCReg(0x20) == 0x3c)
		WriteLPCReg(0xF0, 0);

	EnRXSpecInt(iobase, ON);


	ResetChip(iobase, 5);
	EnableDMA(iobase, OFF);
	EnableTX(iobase, OFF);
	EnableRX(iobase, OFF);
	EnRXDMA(iobase, OFF);
	EnTXDMA(iobase, OFF);
	RXStart(iobase, OFF);
	TXStart(iobase, OFF);
	InitCard(iobase);
	CommonInit(iobase);
	SIRFilter(iobase, ON);
	SetSIR(iobase, ON);
	CRC16(iobase, ON);
	EnTXCRC(iobase, 0);
	WriteReg(iobase, I_ST_CT_0, 0x00);
	SetBaudRate(iobase, 9600);
	SetPulseWidth(iobase, 12);
	SetSendPreambleCount(iobase, 0);

	self->io.speed = 9600;
	self->st_fifo.len = 0;

	via_ircc_change_dongle_speed(iobase, self->io.speed,
				     self->io.dongle_id);

	WriteReg(iobase, I_ST_CT_0, 0x80);
}
