T93C46_Write_Bit(struct sym_device *np, u_char write_bit, u_char *gpreg)
{
	if (write_bit & 0x01)
		*gpreg |= 0x02;
	else
		*gpreg &= 0xfd;

	*gpreg |= 0x10;

	OUTB(np, nc_gpreg, *gpreg);
	INB(np, nc_mbox1);
	udelay(2);

	T93C46_Clk(np, gpreg);
}
