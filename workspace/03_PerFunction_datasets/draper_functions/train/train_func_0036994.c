brinbuildempty(PG_FUNCTION_ARGS)
{
	Relation	index = (Relation) PG_GETARG_POINTER(0);
	Buffer		metabuf;


	metabuf =
		ReadBufferExtended(index, INIT_FORKNUM, P_NEW, RBM_NORMAL, NULL);
	LockBuffer(metabuf, BUFFER_LOCK_EXCLUSIVE);


	START_CRIT_SECTION();
	brin_metapage_init(BufferGetPage(metabuf), BrinGetPagesPerRange(index),
					   BRIN_CURRENT_VERSION);
	MarkBufferDirty(metabuf);
	log_newpage_buffer(metabuf, false);
	END_CRIT_SECTION();

	UnlockReleaseBuffer(metabuf);

	PG_RETURN_VOID();
}
