NVDmaWait(struct fb_info *info, int size)
{
	struct nvidia_par *par = info->par;
	int dmaGet;
	int count = 1000000000, cnt;
	size++;

	while (par->dmaFree < size && --count && !par->lockup) {
		dmaGet = READ_GET(par);

		if (par->dmaPut >= dmaGet) {
			par->dmaFree = par->dmaMax - par->dmaCurrent;
			if (par->dmaFree < size) {
				NVDmaNext(par, 0x20000000);
				if (dmaGet <= SKIPS) {
					if (par->dmaPut <= SKIPS)
						WRITE_PUT(par, SKIPS + 1);
					cnt = 1000000000;
					do {
						dmaGet = READ_GET(par);
					} while (--cnt && dmaGet <= SKIPS);
					if (!cnt) {
						printk("DMA Get lockup\n");
						par->lockup = 1;
					}
				}
				WRITE_PUT(par, SKIPS);
				par->dmaCurrent = par->dmaPut = SKIPS;
				par->dmaFree = dmaGet - (SKIPS + 1);
			}
		} else
			par->dmaFree = dmaGet - par->dmaCurrent - 1;
	}

	if (!count) {
		printk("nvidiafb: DMA Wait Lockup\n");
		nvidiafb_safe_mode(info);
	}
}
