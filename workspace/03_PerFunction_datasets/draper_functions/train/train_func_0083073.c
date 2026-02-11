Xreturn(void)
{
	struct thread *p = runq;
	turfredir();
	while(p->argv) poplist();
	codefree(p->code);
	runq = p->ret;
	efree((char *)p);
	if(runq==0)
		Exit(getstatus());
}
