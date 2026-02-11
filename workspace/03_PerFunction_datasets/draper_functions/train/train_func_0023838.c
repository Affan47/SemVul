do_bmap(fuse_req_t req, fuse_ino_t nodeid, const void *inarg)
{
	struct fuse_bmap_in *arg = (struct fuse_bmap_in *) inarg;

	if (req->f->op.bmap)
		req->f->op.bmap(req, nodeid, arg->blocksize, arg->block);
	else
		fuse_reply_err(req, ENOSYS);
}
