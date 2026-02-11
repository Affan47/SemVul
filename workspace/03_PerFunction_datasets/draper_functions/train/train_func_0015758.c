hf_3(R *cr, R *ci, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 4); m < me; m = m + 1, cr = cr + ms, ci = ci - ms, W = W + 4, MAKE_VOLATILE_STRIDE(rs)) {
	  E T1, Ti, T6, Te, Tb, Tf, Tc, Tj;
	  T1 = cr[0];
	  Ti = ci[0];
	  {
	       E T3, T5, T2, T4;
	       T3 = cr[WS(rs, 1)];
	       T5 = ci[WS(rs, 1)];
	       T2 = W[0];
	       T4 = W[1];
	       T6 = FMA(T2, T3, T4 * T5);
	       Te = FNMS(T4, T3, T2 * T5);
	  }
	  {
	       E T8, Ta, T7, T9;
	       T8 = cr[WS(rs, 2)];
	       Ta = ci[WS(rs, 2)];
	       T7 = W[2];
	       T9 = W[3];
	       Tb = FMA(T7, T8, T9 * Ta);
	       Tf = FNMS(T9, T8, T7 * Ta);
	  }
	  Tc = T6 + Tb;
	  Tj = Te + Tf;
	  {
	       E Td, Tg, Th, Tk;
	       cr[0] = T1 + Tc;
	       Td = FNMS(KP500000000, Tc, T1);
	       Tg = KP866025403 * (Te - Tf);
	       ci[0] = Td - Tg;
	       cr[WS(rs, 1)] = Td + Tg;
	       ci[WS(rs, 2)] = Tj + Ti;
	       Th = KP866025403 * (Tb - T6);
	       Tk = FNMS(KP500000000, Tj, Ti);
	       cr[WS(rs, 2)] = Th - Tk;
	       ci[WS(rs, 1)] = Th + Tk;
	  }
     }
}
