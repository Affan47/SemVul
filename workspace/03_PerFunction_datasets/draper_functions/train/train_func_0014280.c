entername(char *id, int flag)
{	char *cp;
	int i,j,l,result;

	cp=id;
	l=0;
	while (*cp++)
		l++;
	l++;
	if (charbtm-chartop<l)
		fatal("identifier character buffer overflow");
	if (flag) {
		result=chartop;
		j=chartop;
		chartop+=l;
	}
	else {
		charbtm-=l;
		result=charbtm;
		j=charbtm;
	}
	cp=id;
	for (i=0; i<l; i++)
		charheap[j++]=(*cp++);
	return(&charheap[result]);
}
