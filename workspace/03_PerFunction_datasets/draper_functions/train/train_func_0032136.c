Xsub(void)
{
	word *a, *v;
	char *s;
	if(count(runq->argv->next->words)!=1){
		Xerror1("variable name not singleton!");
		return;
	}
	s = runq->argv->next->words->word;
	deglob(s);
	a = runq->argv->next->next->words;
	v = vlook(s)->val;
	a = subwords(v, count(v), runq->argv->words, a);
	poplist();
	poplist();
	runq->argv->words = a;
}
