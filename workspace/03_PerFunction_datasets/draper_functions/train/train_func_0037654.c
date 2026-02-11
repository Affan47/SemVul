da_a(void)
{
	UINT8 res = A + ((PSW & FA) || ((A & 0x0f) > 0x09)) ? 0x06 : 0x00;
	if( (PSW & FC) || ((res & 0xf0) > 0x90) )
		res += 0x60;
	if( res < A )
		PSW |= FC;
	else
		PSW &= ~FC;
	A = res;
}
