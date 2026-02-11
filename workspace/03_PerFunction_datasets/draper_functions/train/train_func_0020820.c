restore(int s)
{	int x;

	x=pop();
	if (s) {
		sp-=code[ic].f1;
		fp=pop();
		ic=pop();
	}
	sp+=code[ic].f2;
	if (sp>STKSIZE)
		runerror("system error: over popup");
	push(x);
}
