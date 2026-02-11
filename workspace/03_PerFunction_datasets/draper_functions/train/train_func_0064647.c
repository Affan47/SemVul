getHeight(void)
{
	int vdb = handleReadW(HW + 0xa8);
	int vde = handleReadW(HW + 0xaa);
	int vmode = handleReadW(HW + 0xc2);


	int yres = vde - vdb;
	if (!(vmode & 0x02))
		yres >>= 1;
	if (vmode & 0x01)
		yres >>= 1;

	return yres;
}
