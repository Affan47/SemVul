poll_timings_nf2(void) {

	ulong dramtlr, dramtlr2, dramtlr3, temp;
	ulong dimm1p, dimm2p, dimm3p;
	float cas;
	int rcd, rp, ras, chan;

	pci_conf_read(0, 0, 1, 0x90, 4, &dramtlr);
	pci_conf_read(0, 0, 1, 0xA0, 4, &dramtlr2);
	pci_conf_read(0, 0, 1, 0x84, 4, &dramtlr3);
	pci_conf_read(0, 0, 2, 0x40, 4, &dimm1p);
	pci_conf_read(0, 0, 2, 0x44, 4, &dimm2p);
	pci_conf_read(0, 0, 2, 0x48, 4, &dimm3p);


	temp = ((dramtlr2 >> 4) & 0x7);
	if (temp == 0x2) { cas = 2; }
	if (temp == 0x3) { cas = 3; }
	if (temp == 0x6) { cas = 2.5; }


	rcd = ((dramtlr >> 20) & 0xF);


	rp = ((dramtlr >> 28) & 0xF);


	ras = ((dramtlr >> 15) & 0xF);


	if ((dimm3p&1) + (dimm2p&1) == 2 || (dimm3p&1) + (dimm1p&1) == 2 ) {
		chan = 2;
	} else {
		chan = 1;
	}
	print_ram_line(cas, rcd, rp, ras, chan);
}
