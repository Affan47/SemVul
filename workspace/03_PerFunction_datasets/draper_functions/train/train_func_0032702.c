do_fsyncdir(fuse_req_t req, fuse_ino_t nodeid, const void *inarg)
{
	struct fuse_fsync_in *arg = (struct fuse_fsync_in *) inarg;
	struct fuse_file_info fi;

	memset(&fi, 0, sizeof(fi));
	fi.fh = arg->fh;
	fi.fh_old = fi.fh;

	if (req->f->op.fsyncdir)
		req->f->op.fsyncdir(req, nodeid, arg->fsync_flags & 1, &fi);
	else
		fuse_reply_err(req, ENOSYS);
}
