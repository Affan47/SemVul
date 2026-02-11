decode_regmask (guint32 regmask)
{
	int i;
	guint32 res;

	res = 0;
	for (i = 0; i < sizeof (callee_saved_regs) / sizeof (int); ++i)
		if (regmask & (1 << i))
			res |= (1 << callee_saved_regs [i]);
	return res;
}
