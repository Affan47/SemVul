vb_bgprombank_w( int bank )
{
	int i;
	unsigned char* color_prom;

	if (bank==vb_bgprombank) return;

	color_prom = memory_region(REGION_PROMS) + bank*0x80;
	for (i=0;i<128;i++, color_prom++) {
		palette_set_color(i,(color_prom[0] & 0x0f) << 4,(color_prom[0] & 0xf0) >> 0,
				       (color_prom[0x800] & 0x0f) << 4);
	}
	vb_bgprombank=bank;
}
