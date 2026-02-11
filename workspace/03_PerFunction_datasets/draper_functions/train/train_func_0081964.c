reply_entry(fuse_req_t req, const struct fuse_entry_param *e,
			int err)
{
	if (!err) {
		struct fuse *f = req_fuse(req);
		if (fuse_reply_entry(req, e) == -ENOENT) {

			if  (e->ino != 0)
				forget_node(f, e->ino, 1);
		}
	} else
		reply_err(req, err);
}
