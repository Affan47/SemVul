aten_connect ( PIA *pi  )

{       pi->saved_r0 = r0();
        pi->saved_r2 = r2();
	w2(0xc);
}
