mei_io_cb_init(struct mei_cl *cl, enum mei_cb_file_ops type,
				 struct file *fp)
{
	struct mei_cl_cb *cb;

	cb = kzalloc(sizeof(struct mei_cl_cb), GFP_KERNEL);
	if (!cb)
		return NULL;

	INIT_LIST_HEAD(&cb->list);
	cb->file_object = fp;
	cb->cl = cl;
	cb->buf_idx = 0;
	cb->fop_type = type;
	return cb;
}
