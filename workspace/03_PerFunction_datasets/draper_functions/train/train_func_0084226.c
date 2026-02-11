MAC_W(UINT32 m, UINT32 n)
{
	INT32 tempm, tempn, dest, src, ans;
	UINT32 templ;

	tempn = (INT32) RW( sh2.r[n] );
	sh2.r[n] += 2;
	tempm = (INT32) RW( sh2.r[m] );
	sh2.r[m] += 2;
	templ = sh2.macl;
	tempm = ((INT32) (short) tempn * (INT32) (short) tempm);
	if ((INT32) sh2.macl >= 0)
		dest = 0;
	else
		dest = 1;
	if ((INT32) tempm >= 0)
	{
		src = 0;
		tempn = 0;
	}
	else
	{
		src = 1;
		tempn = 0xffffffff;
	}
	src += dest;
	sh2.macl += tempm;
	if ((INT32) sh2.macl >= 0)
		ans = 0;
	else
		ans = 1;
	ans += dest;
	if (sh2.sr & S)
	{
		if (ans == 1)
			{
				if (src == 0)
					sh2.macl = 0x7fffffff;
				if (src == 2)
					sh2.macl = 0x80000000;
			}
	}
	else
	{
		sh2.mach += tempn;
		if (templ > sh2.macl)
			sh2.mach += 1;
		}
	sh2_icount -= 2;
}
