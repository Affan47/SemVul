ega16_setpalette(int regno, unsigned red, unsigned green, unsigned blue)
{
	static const unsigned char map[] = { 000, 001, 010, 011 };
	int val;

	if (regno >= 16)
		return;
	val = map[red>>14] | ((map[green>>14]) << 1) | ((map[blue>>14]) << 2);
	vga_io_r(VGA_IS1_RC);
	vga_io_wattr(regno, val);
	vga_io_r(VGA_IS1_RC);
	vga_io_w(VGA_ATT_IW, 0x20);
}
