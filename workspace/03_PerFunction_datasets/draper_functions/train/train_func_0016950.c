Xpopredir(void)
{
	struct redir *rp = runq->redir;
	if(rp==0)
		panic("turfredir null!", 0);
	runq->redir = rp->next;
	if(rp->type==ROPEN)
		close(rp->from);
	efree((char *)rp);
}
