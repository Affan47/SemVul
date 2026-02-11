cob_sub_int (cob_field *f, const int n)
{
	if (unlikely(n == 0)) {
		return 0;
	}
	return cob_add_int (f, -n);
}
