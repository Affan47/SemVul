store_address_masked(CELL cell, F_FIXNUM value, CELL mask, F_FIXNUM shift)
{

	F_FIXNUM test = (F_FIXNUM)mask >> 1;
	if(value <= -test || value >= test)
		critical_error("Value does not fit inside relocation",0);

	u32 original = *(u32*)cell;
	original &= ~mask;
	*(u32*)cell = (original | ((value >> shift) & mask));
}
