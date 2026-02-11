aten_read_regr( PIA *pi, int cont, int regr )

{	int  a, b, r;

        r = regr + cont_map[cont] + 0x40;

	switch (pi->mode) {

        case 0: w0(r); w2(0xe); w2(6);
		w2(7); w2(6); w2(0);
		a = r1(); w0(0x10); b = r1(); w2(0xc);
		return j44(a,b);

        case 1: r |= 0x10;
		w0(r); w2(0xe); w2(6); w0(0xff);
		w2(0x27); w2(0x26); w2(0x20);
		a = r0();
		w2(0x26); w2(0xc);
		return a;
	}
	return -1;
}
