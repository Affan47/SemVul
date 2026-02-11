get_threshold(char *str, threshold *th)
{
	char *p = NULL, i = 0;

	if(!str || !strlen(str) || !th) return -1;


	p = &str[strlen(str) - 1];
	while(p != &str[1]) {
		if(*p == '%') *p = '\0';
		else if(*p == ',' && i) {
			*p = '\0';
			th->pl = (unsigned char)strtoul(p+1, NULL, 0);
			break;
		}
		i = 1;
		p--;
	}
	th->rta = get_timevar(str);

	if(!th->rta) return -1;

	if(th->rta > MAXTTL * 1000000) th->rta = MAXTTL * 1000000;
	if(th->pl > 100) th->pl = 100;

	return 0;
}
