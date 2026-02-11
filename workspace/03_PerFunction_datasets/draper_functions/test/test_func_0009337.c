revent_rpi_alloc(struct nid id, uint32 udata, struct revent_ops *ops)
{
	struct revent_rpc_info *rpi;

	WALLOC(rpi);
	rpi->magic = REVENT_RPI_MAGIC;
	rpi->rid = id;
	rpi->ops = ops;
	rpi->udata = udata;
	rpi->pmi = NULL;

	return rpi;
}
