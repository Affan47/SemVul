objlayout_write_pagelist(struct nfs_pgio_header *hdr, int how)
{
	int err;

	_fix_verify_io_params(hdr->lseg, &hdr->args.pages,
			      &hdr->args.pgbase,
			      hdr->args.offset, hdr->args.count);

	err = objio_write_pagelist(hdr, how);
	if (unlikely(err)) {
		hdr->pnfs_error = err;
		dprintk("%s: Returned Error %d\n", __func__, err);
		return PNFS_NOT_ATTEMPTED;
	}
	return PNFS_ATTEMPTED;
}
