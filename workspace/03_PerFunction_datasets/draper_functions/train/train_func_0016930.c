Xcount(void)
{
	word *a;
	char *s, *t;
	int n;
	char num[12];
	if(count(runq->argv->words)!=1){
		Xerror1("variable name not singleton!");
		return;
	}
	s = runq->argv->words->word;
	deglob(s);
	n = 0;
	for(t = s;'0'<=*t && *t<='9';t++) n = n*10+*t-'0';
	if(n==0 || *t){
		a = vlook(s)->val;
		inttoascii(num, count(a));
	}
	else{
		a = vlook("*")->val;
		inttoascii(num, a && 1<=n && n<=count(a)?1:0);
	}
	poplist();
	pushword(num);
}
