poll_fsb_ct(void)
{
	unsigned long mcr, mdr;
	double dramratio, dramclock, fsb;
	float coef = getP4PMmultiplier();


	mcr = (0x10 << 24);
	mcr += (0x01 << 16);
	mcr += (0x01 << 8);
	mcr &= 0xFFFFFFF0;


	pci_conf_write(0, 0, 0, 0xD0, 4, mcr);


	pci_conf_read(0, 0, 0, 0xD4, 4, &mdr);


	switch (mdr & 0x3) {
		default:
		case 0:	dramratio = 3.0f; break;
		case 1:	dramratio = 4.0f; break;
		case 2:	dramratio = 5.0f; break;
		case 3:	dramratio = 6.0f; break;
	}


	fsb = ((extclock / 1000) / coef);
	dramclock = fsb * dramratio;


	print_cpu_line(dramclock, fsb, 3);

}
