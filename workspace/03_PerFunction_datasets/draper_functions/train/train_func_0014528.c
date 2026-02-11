iitoq(long inum, long iden)
{
	register NUMBER *q;
	long d;
	BOOL sign;

	if (iden == 0) {
		math_error("Division by zero");

	}
	if (inum == 0)
		return qlink(&_qzero_);
	sign = 0;
	if (inum < 0) {
		sign = 1;
		inum = -inum;
	}
	if (iden < 0) {
		sign = 1 - sign;
		iden = -iden;
	}
	d = iigcd(inum, iden);
	inum /= d;
	iden /= d;
	if (iden == 1)
		return itoq(sign ? -inum : inum);
	q = qalloc();
	if (inum != 1)
		itoz(inum, &q->num);
	itoz(iden, &q->den);
	q->num.sign = sign;
	return q;
}
