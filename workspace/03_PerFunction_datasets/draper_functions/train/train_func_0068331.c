neo_init_hw(struct fb_info *info)
{
	struct neofb_par *par = info->par;
	int videoRam = 896;
	int maxClock = 65000;
	int CursorMem = 1024;
	int CursorOff = 0x100;

	DBG("neo_init_hw");

	neoUnlock();

#if 0
	printk(KERN_DEBUG "--- Neo extended register dump ---\n");
	for (int w = 0; w < 0x85; w++)
		printk(KERN_DEBUG "CR %p: %p\n", (void *) w,
		       (void *) vga_rcrt(NULL, w));
	for (int w = 0; w < 0xC7; w++)
		printk(KERN_DEBUG "GR %p: %p\n", (void *) w,
		       (void *) vga_rgfx(NULL, w));
#endif
	switch (info->fix.accel) {
	case FB_ACCEL_NEOMAGIC_NM2070:
		videoRam = 896;
		maxClock = 65000;
		break;
	case FB_ACCEL_NEOMAGIC_NM2090:
	case FB_ACCEL_NEOMAGIC_NM2093:
	case FB_ACCEL_NEOMAGIC_NM2097:
		videoRam = 1152;
		maxClock = 80000;
		break;
	case FB_ACCEL_NEOMAGIC_NM2160:
		videoRam = 2048;
		maxClock = 90000;
		break;
	case FB_ACCEL_NEOMAGIC_NM2200:
		videoRam = 2560;
		maxClock = 110000;
		break;
	case FB_ACCEL_NEOMAGIC_NM2230:
		videoRam = 3008;
		maxClock = 110000;
		break;
	case FB_ACCEL_NEOMAGIC_NM2360:
		videoRam = 4096;
		maxClock = 110000;
		break;
	case FB_ACCEL_NEOMAGIC_NM2380:
		videoRam = 6144;
		maxClock = 110000;
		break;
	}
	switch (info->fix.accel) {
	case FB_ACCEL_NEOMAGIC_NM2070:
	case FB_ACCEL_NEOMAGIC_NM2090:
	case FB_ACCEL_NEOMAGIC_NM2093:
		CursorMem = 2048;
		CursorOff = 0x100;
		break;
	case FB_ACCEL_NEOMAGIC_NM2097:
	case FB_ACCEL_NEOMAGIC_NM2160:
		CursorMem = 1024;
		CursorOff = 0x100;
		break;
	case FB_ACCEL_NEOMAGIC_NM2200:
	case FB_ACCEL_NEOMAGIC_NM2230:
	case FB_ACCEL_NEOMAGIC_NM2360:
	case FB_ACCEL_NEOMAGIC_NM2380:
		CursorMem = 1024;
		CursorOff = 0x1000;

		par->neo2200 = (Neo2200 __iomem *) par->mmio_vbase;
		break;
	}


	par->maxClock = maxClock;
	par->cursorOff = CursorOff;
	return videoRam * 1024;
}
