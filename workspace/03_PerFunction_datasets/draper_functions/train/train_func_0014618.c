ICRB(uae_u32 data)
{
	if (ciabimask & ciabicr) {
		ciabicr |= 0x80;
		INTREQ_0 (0x8000 | data);
	}
	ciabicr_reg |= ciabicr;
}
