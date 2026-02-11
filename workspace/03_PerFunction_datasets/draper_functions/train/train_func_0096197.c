decrypt(unsigned char *r0, unsigned char *r1,
		    unsigned char c0,  unsigned char c1,
		    const unsigned char *table0hi,
		    const unsigned char *table0lo,
		    const unsigned char *table1,
		    int base,
		    int invert)

{
	unsigned char tmp,xor0,xor1;

	tmp = table1[(base & 0xff) ^ address_0_7_xor[(base >> 8) & 0xff]];
	xor0 = (table0hi[(base >> 8) & 0xff] & 0xfe) | (tmp & 0x01);
	xor1 = (tmp & 0xfe) | (table0lo[(base >> 8) & 0xff] & 0x01);

	if (invert)
	{
		*r0 = c1 ^ xor0;
		*r1 = c0 ^ xor1;
	}
	else
	{
		*r0 = c0 ^ xor0;
		*r1 = c1 ^ xor1;
	}
}
