n1_3(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     INT i;
     for (i = v; i > 0; i = i - 1, ri = ri + ivs, ii = ii + ivs, ro = ro + ovs, io = io + ovs, MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  E T1, Ta, T4, T9, T8, Tb, T5, Tc;
	  T1 = ri[0];
	  Ta = ii[0];
	  {
	       E T2, T3, T6, T7;
	       T2 = ri[WS(is, 1)];
	       T3 = ri[WS(is, 2)];
	       T4 = T2 + T3;
	       T9 = KP866025403 * (T3 - T2);
	       T6 = ii[WS(is, 1)];
	       T7 = ii[WS(is, 2)];
	       T8 = KP866025403 * (T6 - T7);
	       Tb = T6 + T7;
	  }
	  ro[0] = T1 + T4;
	  io[0] = Ta + Tb;
	  T5 = FNMS(KP500000000, T4, T1);
	  ro[WS(os, 2)] = T5 - T8;
	  ro[WS(os, 1)] = T5 + T8;
	  Tc = FNMS(KP500000000, Tb, Ta);
	  io[WS(os, 1)] = T9 + Tc;
	  io[WS(os, 2)] = Tc - T9;
     }
}
