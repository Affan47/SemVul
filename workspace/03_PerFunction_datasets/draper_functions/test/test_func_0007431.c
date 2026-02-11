CwLnx_hbar(Driver *drvthis, int x, int y, int len, int promille, int options)
{
    PrivateData *p = drvthis->private_data;

    if (p->ccmode != hbar) {
	unsigned char hBar[p->cellheight];
	int i;

	if (p->ccmode != standard) {

	    report(RPT_WARNING, "%s: hbar: cannot combine two modes using user-defined characters",
		      drvthis->name);
	    return;
	}
	p->ccmode = hbar;

	for (i = 1; i <= p->cellwidth; i++) {

	    memset(hBar, 0xFF & ~((1 << (p->cellwidth - i)) - 1), sizeof(hBar));
#if defined(SEAMLESS_HBARS)
	    CwLnx_set_char_unrestricted(drvthis, i+1, hBar);
#else
	    CwLnx_set_char(drvthis, i+1, hBar);
#endif
	}
    }

    lib_hbar_static(drvthis, x, y, len, promille, options, p->cellwidth, 1);
}
