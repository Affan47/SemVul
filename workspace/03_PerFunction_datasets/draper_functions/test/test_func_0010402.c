arout(void)
{
	Rune	*p1;
	Biobuf	*fi;
	int	c;
	char	*s;
	char	buf[128];

	for (aptr = abuf; *aptr; aptr++) {
		if((*aptr)->command == ACOM) {
			for(p1 = (*aptr)->u.text; *p1; p1++ )
				Bputrune(&fout, *p1);
			Bputc(&fout, '\n');
		} else {
			for(s = buf, p1= (*aptr)->u.text; *p1; p1++)
					s += runetochar(s, p1);
			*s = '\0';
			if((fi = Bopen(buf, OREAD)) == 0)
				continue;
			while((c = Bgetc(fi)) >= 0)
				Bputc(&fout, c);
			Bterm(fi);
		}
	}
	aptr = abuf;
	*aptr = 0;
}
