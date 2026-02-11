do_readdir(fuse_req_t req, fuse_ino_t nodeid, const void *inarg)
{
	struct fuse_read_in *arg = (struct fuse_read_in *) inarg;
	struct fuse_file_info fi;

	memset(&fi, 0, sizeof(fi));
	fi.fh = arg->fh;
	fi.fh_old = fi.fh;

	if (req->f->op.readdir)
		req->f->op.readdir(req, nodeid, arg->size, arg->offset, &fi);
	else
		fuse_reply_err(req, ENOSYS);
}
