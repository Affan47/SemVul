strToTime(char *in)
{
    char *p=in;
    register int ret=0;
    register int i;

    while (1) {
	i=strtol(p,&p,10);
	switch(*p++) {
	case 'w':	ret+=i*7*86400; break;
	case 'd':	ret+=i*86400;	break;
	case 'h':	ret+=i*3600; 	break;
	case 'm':	ret+=i*60; 	break;
	case 's':	ret+=i; 	break;
	case '\0':	return ret;
	}
    }
}
