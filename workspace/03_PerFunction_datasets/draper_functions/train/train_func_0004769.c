YM2608IRQFlagWrite(FM_OPN *OPN, int n, int v)
{
	YM2608 *F2608 = &(FM2608[n]);

	if( v & 0x80 )
	{
		FM_STATUS_RESET(&OPN->ST, 0xf7);
	}
	else
	{
		F2608->flagmask = (~(v&0x1f));
		FM_IRQMASK_SET(&OPN->ST, (F2608->irqmask & F2608->flagmask) );
	}
}
