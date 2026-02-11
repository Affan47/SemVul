lwrt_A(char *p, ftnlen len)
#endif
{
	int a;
	char *p1, *pe;

	a = 0;
	pe = p + len;
	if (f__Aquote) {
		a = 3;
		if (len > 1 && p[len-1] == ' ') {
			while(--len > 1 && p[len-1] == ' ');
			pe = p + len;
			}
		p1 = p;
		while(p1 < pe)
			if (*p1++ == '\'')
				a++;
		}
	if(f__recpos+len+a >= L_len)
		donewrec();
	if (a
#ifndef OMIT_BLANK_CC
		|| !f__recpos
#endif
		)
		PUT(' ');
	if (a) {
		PUT('\'');
		while(p < pe) {
			if (*p == '\'')
				PUT('\'');
			PUT(*p++);
			}
		PUT('\'');
		}
	else
		while(p < pe)
			PUT(*p++);
}
