ib_uverbs_destroy_cq(struct ib_uverbs_file *file,
			     struct ib_device *ib_dev,
			     const char __user *buf, int in_len,
			     int out_len)
{
	struct ib_uverbs_destroy_cq      cmd;
	struct ib_uverbs_destroy_cq_resp resp;
	struct ib_uobject		*uobj;
	struct ib_cq               	*cq;
	struct ib_ucq_object        	*obj;
	struct ib_uverbs_event_file	*ev_file;
	int                        	 ret = -EINVAL;

	if (copy_from_user(&cmd, buf, sizeof cmd))
		return -EFAULT;

	uobj = idr_write_uobj(&ib_uverbs_cq_idr, cmd.cq_handle, file->ucontext);
	if (!uobj)
		return -EINVAL;
	cq      = uobj->object;
	ev_file = cq->cq_context;
	obj     = container_of(cq->uobject, struct ib_ucq_object, uobject);

	ret = ib_destroy_cq(cq);
	if (!ret)
		uobj->live = 0;

	put_uobj_write(uobj);

	if (ret)
		return ret;

	idr_remove_uobj(&ib_uverbs_cq_idr, uobj);

	mutex_lock(&file->mutex);
	list_del(&uobj->list);
	mutex_unlock(&file->mutex);

	ib_uverbs_release_ucq(file, ev_file, obj);

	memset(&resp, 0, sizeof resp);
	resp.comp_events_reported  = obj->comp_events_reported;
	resp.async_events_reported = obj->async_events_reported;

	put_uobj(uobj);

	if (copy_to_user((void __user *) (unsigned long) cmd.response,
			 &resp, sizeof resp))
		return -EFAULT;

	return in_len;
}
