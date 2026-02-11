fstReaderGetCurrentScopeLen(void *ctx)
{
struct fstReaderContext *xc = (struct fstReaderContext *)ctx;

if(xc && xc->curr_hier)
	{
	return(xc->curr_hier->len);
	}

return(0);
}
