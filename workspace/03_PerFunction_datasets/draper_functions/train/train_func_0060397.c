parse_refdes(struct refdes_ *refdes, char *ref_str)
	{
	int i;
	char buff[BUFFSIZE],*cpr,*cp;


	cpr=strstr(ref_str,"=");
	if(cpr==NULL)
		return REFDES_ERROR;
	cp=strstr(ref_str,"?");


	if(cp!=NULL)
		{
		strncpy(&refdes->prefix[0],cpr+1,cp-cpr-1);
		refdes->prefix[cp-cpr-1]='\0';

#ifdef DEBUG
		printf("Prefix=%s\n",&refdes->prefix[0]);
#endif

		return REFDES_WITHOUT_VALUE;
		}
	for(cp=cpr+1,i=0;(*cp != '\n' && *cp>='A' && *cp<='z');++i,++cp)
		buff[i]=*cp;
	buff[i]='\0';
#ifdef DEBUG
	printf("Prefix=%s\n",&buff[0]);
#endif
	strcpy(&refdes->prefix[0],&buff[0]);
	for(i=0,cp;(*cp != '\n' && *cp>='0' && *cp<='9');++cp,++i)
		buff[i]=*cp;
	buff[i]='\0';
#ifdef DEBUG
	printf("Value=%s\n",&buff[0]);
#endif
	refdes->value=abs(atoi(&buff[0]));
	return REFDES_WITH_VALUE;
	}
