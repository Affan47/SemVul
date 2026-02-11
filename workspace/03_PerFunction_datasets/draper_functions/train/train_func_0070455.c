r2cfII_3(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     {
	  INT i;
	  for (i = v; i > 0; i = i - 1, R0 = R0 + ivs, R1 = R1 + ivs, Cr = Cr + ovs, Ci = Ci + ovs, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(csr), MAKE_VOLATILE_STRIDE(csi)) {
	       E T3, T1, T2, T4;
	       T3 = R0[0];
	       T1 = R1[0];
	       T2 = R0[WS(rs, 1)];
	       Ci[0] = -(KP866025403 * (T1 + T2));
	       T4 = T2 - T1;
	       Cr[WS(csr, 1)] = T3 + T4;
	       Cr[0] = FNMS(KP500000000, T4, T3);
	  }
     }
}
