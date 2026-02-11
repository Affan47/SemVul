poll_fsb_i945(void) {

	double dramclock, dramratio, fsb;
	unsigned long mchcfg, dev0;
	float coef = getP4PMmultiplier();
	long *ptr;


	pci_conf_read( 0, 0, 0, 0x44, 4, &dev0);
	dev0 &= 0xFFFFC000;
	ptr=(long*)(dev0+0xC00);
	mchcfg = *ptr & 0xFFFF;
	dramratio = 1;

	switch ((mchcfg >> 4)&7) {
		case 1:	dramratio = 1.0; break;
		case 2:	dramratio = 1.33334; break;
		case 3:	dramratio = 1.66667; break;
		case 4:	dramratio = 2.0; break;
	}


	fsb = ((extclock / 1000) / coef);

	dramclock = fsb * dramratio;


	print_cpu_line(dramclock, fsb, 2);

}
