hb_3(R *cr, R *ci, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 4); m < me; m = m + 1, cr = cr + ms, ci = ci - ms, W = W + 4, MAKE_VOLATILE_STRIDE(rs)) {
	  E T1, T4, Ta, Te, T5, T8, Tb, Tf;
	  {
	       E T2, T3, T6, T7;
	       T1 = cr[0];
	       T2 = cr[WS(rs, 1)];
	       T3 = ci[0];
	       T4 = T2 + T3;
	       Ta = FNMS(KP500000000, T4, T1);
	       Te = KP866025403 * (T2 - T3);
	       T5 = ci[WS(rs, 2)];
	       T6 = ci[WS(rs, 1)];
	       T7 = cr[WS(rs, 2)];
	       T8 = T6 - T7;
	       Tb = KP866025403 * (T6 + T7);
	       Tf = FNMS(KP500000000, T8, T5);
	  }
	  cr[0] = T1 + T4;
	  ci[0] = T5 + T8;
	  {
	       E Tc, Tg, T9, Td;
	       Tc = Ta - Tb;
	       Tg = Te + Tf;
	       T9 = W[0];
	       Td = W[1];
	       cr[WS(rs, 1)] = FNMS(Td, Tg, T9 * Tc);
	       ci[WS(rs, 1)] = FMA(T9, Tg, Td * Tc);
	  }
	  {
	       E Ti, Tk, Th, Tj;
	       Ti = Ta + Tb;
	       Tk = Tf - Te;
	       Th = W[2];
	       Tj = W[3];
	       cr[WS(rs, 2)] = FNMS(Tj, Tk, Th * Ti);
	       ci[WS(rs, 2)] = FMA(Th, Tk, Tj * Ti);
	  }
     }
}
