r2cf_8(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     {
	  INT i;
	  for (i = v; i > 0; i = i - 1, R0 = R0 + ivs, R1 = R1 + ivs, Cr = Cr + ovs, Ci = Ci + ovs, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(csr), MAKE_VOLATILE_STRIDE(csi)) {
	       E T4, T7, T3, Tj, Td, T5, T8, T9;
	       {
		    E T1, T2, Tb, Tc;
		    T1 = R0[0];
		    T2 = R0[WS(rs, 2)];
		    Tb = R1[WS(rs, 3)];
		    Tc = R1[WS(rs, 1)];
		    T4 = R0[WS(rs, 1)];
		    T7 = T1 - T2;
		    T3 = T1 + T2;
		    Tj = Tb + Tc;
		    Td = Tb - Tc;
		    T5 = R0[WS(rs, 3)];
		    T8 = R1[0];
		    T9 = R1[WS(rs, 2)];
	       }
	       {
		    E T6, Tf, Ta, Ti;
		    T6 = T4 + T5;
		    Tf = T4 - T5;
		    Ta = T8 - T9;
		    Ti = T8 + T9;
		    {
			 E Th, Tk, Te, Tg;
			 Th = T3 + T6;
			 Cr[WS(csr, 2)] = T3 - T6;
			 Tk = Ti + Tj;
			 Ci[WS(csi, 2)] = Tj - Ti;
			 Te = Ta + Td;
			 Tg = Td - Ta;
			 Cr[0] = Th + Tk;
			 Cr[WS(csr, 4)] = Th - Tk;
			 Ci[WS(csi, 3)] = FMA(KP707106781, Tg, Tf);
			 Ci[WS(csi, 1)] = FMS(KP707106781, Tg, Tf);
			 Cr[WS(csr, 1)] = FMA(KP707106781, Te, T7);
			 Cr[WS(csr, 3)] = FNMS(KP707106781, Te, T7);
		    }
	       }
	  }
     }
}
