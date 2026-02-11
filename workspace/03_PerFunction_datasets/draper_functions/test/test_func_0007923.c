do_btst(type8 a)
{
	a &= admode ? 0x7 : 0x1f;
	while (admode == 0 && a >= 8)
	{
		a -= 8;
		arg1 -= 1;
	}
	zflag = 0;
	if ((arg1[0] & (1 << a)) == 0)
		zflag = 0xff;
	return a;
}
