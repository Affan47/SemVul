unix_to_nt_time(TDS_UINT8 * nt, time_t t)
{
#define TIME_FIXUP_CONSTANT (((TDS_UINT8) 134774U) * 86400U)

	TDS_UINT8 t2;

	if (t == (time_t) - 1) {
		*nt = (TDS_UINT8) - ((TDS_INT8) 1);
		return;
	}
	if (t == 0) {
		*nt = 0;
		return;
	}

	t2 = t;
	t2 += TIME_FIXUP_CONSTANT;
	t2 *= 1000 * 1000 * 10;

	*nt = t2;
}
