hvutil_transport_init(const char *name,
					       u32 cn_idx, u32 cn_val,
					       int (*on_msg)(void *, int),
					       void (*on_reset)(void))
{
	struct hvutil_transport *hvt;

	hvt = kzalloc(sizeof(*hvt), GFP_KERNEL);
	if (!hvt)
		return NULL;

	hvt->cn_id.idx = cn_idx;
	hvt->cn_id.val = cn_val;

	hvt->mdev.minor = MISC_DYNAMIC_MINOR;
	hvt->mdev.name = name;

	hvt->fops.owner = THIS_MODULE;
	hvt->fops.read = hvt_op_read;
	hvt->fops.write = hvt_op_write;
	hvt->fops.poll = hvt_op_poll;
	hvt->fops.open = hvt_op_open;
	hvt->fops.release = hvt_op_release;

	hvt->mdev.fops = &hvt->fops;

	init_waitqueue_head(&hvt->outmsg_q);
	mutex_init(&hvt->lock);
	init_completion(&hvt->release);

	spin_lock(&hvt_list_lock);
	list_add(&hvt->list, &hvt_list);
	spin_unlock(&hvt_list_lock);

	hvt->on_msg = on_msg;
	hvt->on_reset = on_reset;

	if (misc_register(&hvt->mdev))
		goto err_free_hvt;


	if (hvt->cn_id.idx > 0 && hvt->cn_id.val > 0 &&
	    cn_add_callback(&hvt->cn_id, name, hvt_cn_callback))
		goto err_free_hvt;

	return hvt;

err_free_hvt:
	spin_lock(&hvt_list_lock);
	list_del(&hvt->list);
	spin_unlock(&hvt_list_lock);
	kfree(hvt);
	return NULL;
}
