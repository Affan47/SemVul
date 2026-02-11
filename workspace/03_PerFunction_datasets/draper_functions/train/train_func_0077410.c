UnitTest(const char* p) {
	printf("params=\"%s\"\n",p);
	char buf[1024] = {0};
	if(p)
		strncpy(buf,p,sizeof(buf));
	HttpParams params(p? buf: NULL);
	int count=0;
	while(params.next() && count<10) {
		count++;
		printf("\t%d: key=\"%s\", value=\"%s\"\n",count,params.key(),params.value());
		printf("\t\tparams=\"%s\"\n",buf);
	}
	params.reset();
	printf("\tbefore: \"%s\"\n\tafter:  \"%s\"\n",p,buf);
	count=0;
	while(params.next() && count<10) {
		count++;
		printf("\t%d: key=\"%s\", value=\"%s\"\n",count,params.key(),params.value());
		printf("\t\tparams=\"%s\"\n",buf);
	}
}
