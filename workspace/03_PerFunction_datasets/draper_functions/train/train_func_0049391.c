nvidiafb_set_par(struct fb_info *info)
{
	struct nvidia_par *par = info->par;

	NVTRACE_ENTER();

	NVLockUnlock(par, 1);
	if (!par->FlatPanel || !par->twoHeads)
		par->FPDither = 0;

	if (par->FPDither < 0) {
		if ((par->Chipset & 0x0ff0) == 0x0110)
			par->FPDither = !!(NV_RD32(par->PRAMDAC, 0x0528)
					   & 0x00010000);
		else
			par->FPDither = !!(NV_RD32(par->PRAMDAC, 0x083C) & 1);
		printk(KERN_INFO PFX "Flat panel dithering %s\n",
		       par->FPDither ? "enabled" : "disabled");
	}

	info->fix.visual = (info->var.bits_per_pixel == 8) ?
	    FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_DIRECTCOLOR;

	nvidia_init_vga(info);
	nvidia_calc_regs(info);

	NVLockUnlock(par, 0);
	if (par->twoHeads) {
		VGA_WR08(par->PCIO, 0x03D4, 0x44);
		VGA_WR08(par->PCIO, 0x03D5, par->ModeReg.crtcOwner);
		NVLockUnlock(par, 0);
	}

	nvidia_screen_off(par, 1);

	nvidia_write_regs(par, &par->ModeReg);
	NVSetStartAddress(par, 0);

#if defined (__BIG_ENDIAN)

	{
		unsigned char tmp;

		VGA_WR08(par->PCIO, 0x3d4, 0x46);
		tmp = VGA_RD08(par->PCIO, 0x3d5);
		tmp |= (1 << 7);
		VGA_WR08(par->PCIO, 0x3d5, tmp);
    }
#endif

	info->fix.line_length = (info->var.xres_virtual *
				 info->var.bits_per_pixel) >> 3;
	if (info->var.accel_flags) {
		info->fbops->fb_imageblit = nvidiafb_imageblit;
		info->fbops->fb_fillrect = nvidiafb_fillrect;
		info->fbops->fb_copyarea = nvidiafb_copyarea;
		info->fbops->fb_sync = nvidiafb_sync;
		info->pixmap.scan_align = 4;
		info->flags &= ~FBINFO_HWACCEL_DISABLED;
		info->flags |= FBINFO_READS_FAST;
		NVResetGraphics(info);
	} else {
		info->fbops->fb_imageblit = cfb_imageblit;
		info->fbops->fb_fillrect = cfb_fillrect;
		info->fbops->fb_copyarea = cfb_copyarea;
		info->fbops->fb_sync = NULL;
		info->pixmap.scan_align = 1;
		info->flags |= FBINFO_HWACCEL_DISABLED;
		info->flags &= ~FBINFO_READS_FAST;
	}

	par->cursor_reset = 1;

	nvidia_screen_off(par, 0);

#ifdef CONFIG_BOOTX_TEXT

	btext_update_display(info->fix.smem_start,
			     info->var.xres, info->var.yres,
			     info->var.bits_per_pixel, info->fix.line_length);
#endif

	NVLockUnlock(par, 0);
	NVTRACE_LEAVE();
	return 0;
}
