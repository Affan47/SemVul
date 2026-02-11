is_aligned_req(struct nfs_pageio_descriptor *pgio,
		struct nfs_page *req, unsigned int alignment)
{


	if (pgio->pg_dreq == NULL)
		return true;

	if (!IS_ALIGNED(req->wb_offset, alignment))
		return false;

	if (IS_ALIGNED(req->wb_bytes, alignment))
		return true;

	if (req_offset(req) + req->wb_bytes == i_size_read(pgio->pg_inode)) {


		return true;
	}

	return false;
}
