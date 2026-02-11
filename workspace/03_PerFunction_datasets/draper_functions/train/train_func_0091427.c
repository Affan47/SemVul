set_565 (struct imstt_par *par)
{
	if (par->ramdac == IBM) {
		par->cmap_regs[PIDXHI] = 0;		eieio();
		par->cmap_regs[PIDXLO] = BPP16;		eieio();
		par->cmap_regs[PIDXDATA] = 0x03;	eieio();
	} else {
		par->cmap_regs[TVPADDRW] = TVPIRTCC;	eieio();
		par->cmap_regs[TVPIDATA] = 0x45;	eieio();
	}
}
