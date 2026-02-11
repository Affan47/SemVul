v4l2_ctrl_handler_init_class(struct v4l2_ctrl_handler *hdl,
				 unsigned nr_of_controls_hint,
				 struct lock_class_key *key, const char *name)
{
	hdl->lock = &hdl->_lock;
	mutex_init(hdl->lock);
	lockdep_set_class_and_name(hdl->lock, key, name);
	INIT_LIST_HEAD(&hdl->ctrls);
	INIT_LIST_HEAD(&hdl->ctrl_refs);
	hdl->nr_of_buckets = 1 + nr_of_controls_hint / 8;
	hdl->buckets = kcalloc(hdl->nr_of_buckets, sizeof(hdl->buckets[0]),
			       GFP_KERNEL);
	hdl->error = hdl->buckets ? 0 : -ENOMEM;
	return hdl->error;
}
