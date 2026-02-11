r2cfII_5(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP587785252, +0.587785252292473129168705954639072768597652438);
     INT i;
     for (i = v; i > 0; i = i - 1, R0 = R0 + ivs, R1 = R1 + ivs, Cr = Cr + ovs, Ci = Ci + ovs, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(csr), MAKE_VOLATILE_STRIDE(csi)) {
	  E T8, T3, T6, T9, Tc, Tb, T7, Ta;
	  T8 = R0[0];
	  {
	       E T1, T2, T4, T5;
	       T1 = R0[WS(rs, 1)];
	       T2 = R1[WS(rs, 1)];
	       T3 = T1 - T2;
	       T4 = R0[WS(rs, 2)];
	       T5 = R1[0];
	       T6 = T4 - T5;
	       T9 = T3 + T6;
	       Tc = T4 + T5;
	       Tb = T1 + T2;
	  }
	  Cr[WS(csr, 2)] = T8 + T9;
	  Ci[WS(csi, 1)] = FNMS(KP951056516, Tc, KP587785252 * Tb);
	  Ci[0] = -(FMA(KP951056516, Tb, KP587785252 * Tc));
	  T7 = KP559016994 * (T3 - T6);
	  Ta = FNMS(KP250000000, T9, T8);
	  Cr[0] = T7 + Ta;
	  Cr[WS(csr, 1)] = Ta - T7;
     }
}
