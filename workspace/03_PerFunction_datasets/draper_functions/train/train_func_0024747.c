inventory()
{
	char msg;
	int i;

	msg = 98;
	for (i=1; i<=MAXOBJ; ++i) {
		if (i==BEAR || !toting(i))
			continue;
		if (msg)
			rspeak(99);
		msg = 0;
		pspeak(i,-1);
	}
	if (toting(BEAR))
		msg = 141;
	if (msg)
		rspeak(msg);
}
