ExpandKadds(line, el)

	char *line;

	char *el;

{
	auto char	dlm,
			*kp,
			*sl = line,
			*elp = el,
			*symbol;

	char num[15];
	auto unsigned long int value;

	auto struct symbol sym;


	if ( i_am_paranoid &&
	     (strstr(line, "Oops:") != (char *) 0) && !InitMsyms() )
		Syslog(LOG_WARNING, "Cannot load kernel module symbols.\n");


	if ( (num_syms == 0) ||
	     (kp = strstr(line, "[<")) == (char *) 0 )
	{
		strcpy(el, line);
		return(el);
	}


	do
	{
		while ( sl < kp+1 )
			*elp++ = *sl++;


	        if ( (kp = strstr(sl, ">]")) == (char *) 0 )
		{
			strcpy(el, sl);
			return(el);
		}
		dlm = *kp;
		strncpy(num,sl+1,kp-sl-1);
		num[kp-sl-1] = '\0';
		value = strtoul(num, (char **) 0, 16);
		if ( (symbol = LookupSymbol(value, &sym)) == (char *) 0 )
			symbol = sl;

		strcat(elp, symbol);
		elp += strlen(symbol);
		if ( debugging )
			fprintf(stderr, "Symbol: %s = %lx = %s, %x/%d\n", \
				sl+1, value, \
				(sym.size==0) ? symbol+1 : symbol, \
				sym.offset, sym.size);

		value = 2;
		if ( sym.size != 0 )
		{
			--value;
			++kp;
			elp += sprintf(elp, "+%x/%d", sym.offset, sym.size);
		}
		strncat(elp, kp, value);
		elp += value;
		sl = kp + value;
		if ( (kp = strstr(sl, "[<")) == (char *) 0 )
			strcat(elp, sl);
	}
	while ( kp != (char *) 0);

	if ( debugging )
		fprintf(stderr, "Expanded line: %s\n", el);
	return(el);
}
