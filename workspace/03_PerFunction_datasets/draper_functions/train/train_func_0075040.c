on26_disconnect ( PIA *pi )

{       if (pi->mode >= 2) { w3(4); w3(4); w3(4); w3(4); }
	              else { w0(4); P1; w0(4); P1; }
	CCP(0x30);
        w0(pi->saved_r0);
        w2(pi->saved_r2);
}
