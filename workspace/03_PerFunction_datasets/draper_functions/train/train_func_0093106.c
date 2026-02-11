fixmulaccum(quadint *q,fix a,fix b)
{
	u_int32_t aa,bb;
	u_int32_t ah,al,bh,bl;
	u_int32_t t,c=0,old;
	int neg;

	neg = ((a^b) < 0);

	aa = labs(a); bb = labs(b);

	ah = aa>>16;  al = aa&0xffff;
	bh = bb>>16;  bl = bb&0xffff;

	t = ah*bl + bh*al;

	if (neg)
		fixquadnegate(q);

	old = q->low;
	q->low += al*bl;
	if (q->low < old) q->high++;

	old = q->low;
	q->low += (t<<16);
	if (q->low < old) q->high++;

	q->high += ah*bh + (t>>16) + c;

	if (neg)
		fixquadnegate(q);

}
