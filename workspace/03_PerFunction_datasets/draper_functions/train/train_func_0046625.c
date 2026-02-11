fstReaderGetDumpActivityChangeValue(void *ctx, uint32_t idx)
{
struct fstReaderContext *xc = (struct fstReaderContext *)ctx;

if(xc && (idx < xc->num_blackouts) && (xc->blackout_activity))
	{
	return(xc->blackout_activity[idx]);
	}
	else
	{
	return(0);
	}
}
