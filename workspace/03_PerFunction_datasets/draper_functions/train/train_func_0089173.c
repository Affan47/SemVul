__fpclassifyf(float f)
{
	union IEEEf2bits u;

	u.f = f;
	if (u.bits.exp == 255) {
	   if (u.bits.man == 0) {
		   return FP_INFINITE;
	   } else {
		   return FP_NAN;
	   }
	} else if (u.bits.exp != 0) {
		return FP_NORMAL;
	} else if (u.bits.man == 0) {
		return FP_ZERO;
	} else {
		return FP_SUBNORMAL;
	}
}
