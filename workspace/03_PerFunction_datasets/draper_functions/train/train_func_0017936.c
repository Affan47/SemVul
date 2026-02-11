FAN_TO_REG(long val, int tpc)
{
	if (tpc) {
		return clamp_val(val / tpc, 0, 0xffff);
	} else {
		return (val <= 0) ? 0xffff :
			clamp_val(90000 * 60 / val, 0, 0xfffe);
	}
}
