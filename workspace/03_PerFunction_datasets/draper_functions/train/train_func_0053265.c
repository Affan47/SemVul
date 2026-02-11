aty128_find_mem_vbios(struct aty128fb_par *par)
{


        u32  segstart;
        unsigned char __iomem *rom_base = NULL;

        for (segstart=0x000c0000; segstart<0x000f0000; segstart+=0x00001000) {
                rom_base = ioremap(segstart, 0x10000);
		if (rom_base == NULL)
			return NULL;
		if (readb(rom_base) == 0x55 && readb(rom_base + 1) == 0xaa)
	                break;
                iounmap(rom_base);
		rom_base = NULL;
        }
	return rom_base;
}
