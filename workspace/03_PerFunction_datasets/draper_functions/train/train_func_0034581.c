do_opendir(fuse_req_t req, fuse_ino_t nodeid, const void *inarg)
{
	struct fuse_open_in *arg = (struct fuse_open_in *) inarg;
	struct fuse_file_info fi;

	memset(&fi, 0, sizeof(fi));
	fi.flags = arg->flags;

	if (req->f->op.opendir)
		req->f->op.opendir(req, nodeid, &fi);
	else
		fuse_reply_open(req, &fi);
}
