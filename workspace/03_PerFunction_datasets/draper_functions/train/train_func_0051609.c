psecs(l,cp)
long l;
register char *cp;
{
	register int i;

	i = l / 3600;
	if (i) {
		sprintf(cp,"%d:", i);
		END(cp);
		i = l % 3600;
		sprintf(cp,"%d%d", (i/60) / 10, (i/60) % 10);
		END(cp);
	} else {
		i = l;
		sprintf(cp,"%d", i / 60);
		END(cp);
	}
	i %= 60;
	*cp++ = ':';
	sprintf(cp,"%d%d", i / 10, i % 10);
}
