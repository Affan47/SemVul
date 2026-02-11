read_reg(int i, int s)
{
	type8 *ptr;

	if (i > 15)
	{
		ms_fatal("invalid register in read_reg");
		return 0;
	}
	if (i < 8)
		ptr = (type8 *) & dreg[i];
	else
		ptr = (type8 *) & areg[i - 8];

	switch (s)
	{
	case 0:
		return reg_align(ptr, 0)[0];
	case 1:
		return read_w(reg_align(ptr, 1));
	default:
		return read_l(ptr);
	}
}
