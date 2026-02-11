uutoq(FULL inum, FULL iden)
{
	register NUMBER *q;
	FULL d;
	BOOL sign;

	if (iden == 0) {
		math_error("Division by zero");

	}
	if (inum == 0)
		return qlink(&_qzero_);
	sign = 0;
	d = uugcd(inum, iden);
	inum /= d;
	iden /= d;
	if (iden == 1)
		return utoq(inum);
	q = qalloc();
	if (inum != 1)
		utoz(inum, &q->num);
	utoz(iden, &q->den);
	q->num.sign = sign;
	return q;
}
