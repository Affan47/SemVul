epia_read_regr( PIA *pi, int cont, int regr )

{       int     a, b, r;

	regr += cont_map[cont];

        switch (pi->mode)  {

        case 0: r = regr^0x39;
                w0(r); w2(1); w2(3); w0(r);
                a = r1(); w2(1); b = r1(); w2(4);
                return j44(a,b);

        case 1: r = regr^0x31;
                w0(r); w2(1); w0(r&0x37);
                w2(3); w2(5); w0(r|0xf0);
                a = r1(); b = r2(); w2(4);
                return j53(a,b);

        case 2: r = regr^0x29;
                w0(r); w2(1); w2(0X21); w2(0x23);
                a = r0(); w2(4);
                return a;

	case 3:
	case 4:
        case 5: w3(regr); w2(0x24); a = r4(); w2(4);
                return a;

        }
        return -1;
}
