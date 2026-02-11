next_pow2_int(long num)
{
	if (num > INT_MAX / 2)
		num = INT_MAX / 2;
	return 1 << my_log2(num);
}
