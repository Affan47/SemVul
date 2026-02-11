cx24123_int_log2(u32 a, u32 b)
{
	u32 exp, nearest = 0;
	u32 div = a / b;
	if (a % b >= b / 2)
		++div;
	if (div < (1 << 31)) {
		for (exp = 1; div > exp; nearest++)
			exp += exp;
	}
	return nearest;
}
