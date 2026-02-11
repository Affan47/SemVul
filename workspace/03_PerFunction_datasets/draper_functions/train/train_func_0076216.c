on20_read_regr( PIA *pi, int cont, int regr )

{	int h,l, r ;

        r = (regr<<2) + 1 + cont;

        op(1); vl(r); op(0);

	switch (pi->mode)  {

        case 0:  w2(4); w2(6); l = r1();
                 w2(4); w2(6); h = r1();
                 w2(4); w2(6); w2(4); w2(6); w2(4);
		 return j44(l,h);

	case 1:  w2(4); w2(0x26); r = r0();
                 w2(4); w2(0x26); w2(4);
		 return r;

	}
	return -1;
}
