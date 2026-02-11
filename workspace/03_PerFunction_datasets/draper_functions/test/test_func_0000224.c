defout(int last)
{
	int i, c;
	char sar[NAMESIZE+10];

	for(i=ndefout; i<=ntokens; i++) {

		c = tokset[i].name[0];
		if(c != ' ' && c != '$') {
			Bprint(ftable, "#define	%s	%d\n",
				tokset[i].name, tokset[i].value);
			if(fdefine)
				Bprint(fdefine, "#define\t%s\t%d\n",
					tokset[i].name, tokset[i].value);
		}
	}
	ndefout = ntokens+1;
	if(last && fdebug) {
		Bprint(fdebug, "static	char*	yytoknames[] =\n{\n");
		TLOOP(i) {
			if(tokset[i].name) {
				chcopy(sar, tokset[i].name);
				Bprint(fdebug, "\t\"%s\",\n", sar);
				continue;
			}
			Bprint(fdebug, "\t0,\n");
		}
		Bprint(fdebug, "};\n");
	}
}
