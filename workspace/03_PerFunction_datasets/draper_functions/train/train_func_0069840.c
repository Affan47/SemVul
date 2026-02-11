serialVFD_hbar (Driver *drvthis, int x, int y, int len, int promille, int options)
{
	PrivateData *p = drvthis->private_data;

	if (p->customchars >= p->cellwidth || p->predefined_hbar == 1) {
		serialVFD_init_hbar(drvthis);
		lib_hbar_static(drvthis, x, y, len, promille, options, p->cellwidth, p->hbar_cc_offset);
	}
	else {
		lib_hbar_static(drvthis, x, y, len, promille, options, 2, 0x2C);
	}
}
