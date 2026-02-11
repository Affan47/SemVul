kill_pipe(struct pipe *p)
{
	close(p->prod);
	close(p->cons);
	pool_free2(pool2_pipe, p);
	pipes_used--;
	return;
}
