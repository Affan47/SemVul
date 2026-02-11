xdr_decode(nfs_readdir_descriptor_t *desc,
		      struct nfs_entry *entry, struct xdr_stream *xdr)
{
	int error;

	error = desc->decode(xdr, entry, desc->plus);
	if (error)
		return error;
	entry->fattr->time_start = desc->timestamp;
	entry->fattr->gencount = desc->gencount;
	return 0;
}
