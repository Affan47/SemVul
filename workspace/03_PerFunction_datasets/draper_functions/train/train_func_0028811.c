is_all_zeros(void * const x_, size_t sz)
{

	u32 *x = x_;
	int n;

	for (n = 0; n < sz / sizeof(*x); n++)
		if (x[n])
			return false;

	return true;
}
