f_btrunc(int count, NUMBER **vals)
{
	NUMBER *val;

	val = qlink(&_qzero_);
	if (count == 2)
		val = vals[1];
	return qbtrunc(*vals, val);
}
