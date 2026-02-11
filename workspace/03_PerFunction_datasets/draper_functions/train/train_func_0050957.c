fstWriterEmitDumpActive(void *ctx, int enable)
{
struct fstWriterContext *xc = (struct fstWriterContext *)ctx;

if(xc)
	{
	struct fstBlackoutChain *b = calloc(1, sizeof(struct fstBlackoutChain));

	b->tim = xc->curtime;
	b->active = (enable != 0);

	xc->num_blackouts++;
	if(xc->blackout_curr)
		{
		xc->blackout_curr->next = b;
		xc->blackout_curr = b;
		}
		else
		{
		xc->blackout_head = b;
		xc->blackout_curr = b;
		}
	}
}
