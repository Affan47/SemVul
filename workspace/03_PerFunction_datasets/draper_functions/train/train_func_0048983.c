hc2cb_2(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     {
	  INT m;
	  for (m = mb, W = W + ((mb - 1) * 2); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 2, MAKE_VOLATILE_STRIDE(8, rs)) {
	       E T1, T2, T6, T3, T4, T8, T5, T7;
	       T1 = Rp[0];
	       T2 = Rm[0];
	       T6 = T1 - T2;
	       T3 = Ip[0];
	       T4 = Im[0];
	       T8 = T3 + T4;
	       Rp[0] = T1 + T2;
	       Rm[0] = T3 - T4;
	       T5 = W[0];
	       T7 = W[1];
	       Ip[0] = FNMS(T7, T8, T5 * T6);
	       Im[0] = FMA(T7, T6, T5 * T8);
	  }
     }
}
