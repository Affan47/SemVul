n_setfont(int a)
{
	int i, j;

	if (a)
		i = getrq();
	else
		i = getsn();
	if (!i || i == 'P') {
		j = font1;
		goto s0;
	}
	if (i == 'S' || i == '0')
		return;
	if ((j = findft(i)) == -1)
		return;
s0:
	font1 = font;
	font = j;
	mchbits();
}
