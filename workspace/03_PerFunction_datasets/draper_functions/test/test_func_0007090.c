sDisInterrupts(CHANNEL_T * ChP, Word_t Flags)
{
	Byte_t Mask;

	ChP->RxControl[2] &=
	    ~((Byte_t) Flags & (RXINT_EN | SRCINT_EN | MCINT_EN));
	out32(ChP->IndexAddr, ChP->RxControl);
	ChP->TxControl[2] &= ~((Byte_t) Flags & TXINT_EN);
	out32(ChP->IndexAddr, ChP->TxControl);

	if (Flags & CHANINT_EN) {
		Mask = sInB(ChP->IntMask) & sBitMapClrTbl[ChP->ChanNum];
		sOutB(ChP->IntMask, Mask);
	}
}
