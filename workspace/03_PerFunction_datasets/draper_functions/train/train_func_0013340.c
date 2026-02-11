brin_tuples_equal(const BrinTuple *a, Size alen, const BrinTuple *b, Size blen)
{
	if (alen != blen)
		return false;
	if (memcmp(a, b, alen) != 0)
		return false;
	return true;
}
