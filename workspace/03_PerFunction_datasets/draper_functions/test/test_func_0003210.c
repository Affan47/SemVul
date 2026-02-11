qround(NUMBER *q, long places, long rnd)
{
	NUMBER *e, *r;

	if (qiszero(q))
		return qlink(&_qzero_);
	if (rnd & 32)
		places -= qilog10(q) + 1;
	e = qtenpow(-places);
	r = qmappr(q, e, rnd & 31);
	qfree(e);
	return r;
}
