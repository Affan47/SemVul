CwLnx_vbar(Driver *drvthis, int x, int y, int len, int promille, int options)
{
    PrivateData *p = drvthis->private_data;

    if (p->ccmode != vbar) {
	unsigned char vBar[p->cellheight];
	int i;

	if (p->ccmode != standard) {

	    report(RPT_WARNING, "%s: vbar: cannot combine two modes using user-defined characters",
		      drvthis->name);
	    return;
	}
	p->ccmode = vbar;

	memset(vBar, 0x00, sizeof(vBar));

	for (i = 1; i < p->cellheight; i++) {

	    vBar[p->cellheight - i] = 0xFF;
	    CwLnx_set_char(drvthis, i+1, vBar);
	}
    }

    lib_vbar_static(drvthis, x, y, len, promille, options, p->cellheight, 1);
}
