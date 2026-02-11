tx_chunk_destroy(txdrv_t *tx)
{
	struct attr *attr = tx->opaque;

	WFREE(attr);
}
