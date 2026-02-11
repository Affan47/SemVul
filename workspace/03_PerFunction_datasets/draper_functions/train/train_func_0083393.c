ib_uverbs_destroy_srq(struct ib_uverbs_file *file,
			      struct ib_device *ib_dev,
			      const char __user *buf, int in_len,
			      int out_len)
{
	struct ib_uverbs_destroy_srq      cmd;
	struct ib_uverbs_destroy_srq_resp resp;
	struct ib_uobject		 *uobj;
	struct ib_srq               	 *srq;
	struct ib_uevent_object        	 *obj;
	int                         	  ret = -EINVAL;
	struct ib_usrq_object		 *us;
	enum ib_srq_type		  srq_type;

	if (copy_from_user(&cmd, buf, sizeof cmd))
		return -EFAULT;

	uobj = idr_write_uobj(&ib_uverbs_srq_idr, cmd.srq_handle, file->ucontext);
	if (!uobj)
		return -EINVAL;
	srq = uobj->object;
	obj = container_of(uobj, struct ib_uevent_object, uobject);
	srq_type = srq->srq_type;

	ret = ib_destroy_srq(srq);
	if (!ret)
		uobj->live = 0;

	put_uobj_write(uobj);

	if (ret)
		return ret;

	if (srq_type == IB_SRQT_XRC) {
		us = container_of(obj, struct ib_usrq_object, uevent);
		atomic_dec(&us->uxrcd->refcnt);
	}

	idr_remove_uobj(&ib_uverbs_srq_idr, uobj);

	mutex_lock(&file->mutex);
	list_del(&uobj->list);
	mutex_unlock(&file->mutex);

	ib_uverbs_release_uevent(file, obj);

	memset(&resp, 0, sizeof resp);
	resp.events_reported = obj->events_reported;

	put_uobj(uobj);

	if (copy_to_user((void __user *) (unsigned long) cmd.response,
			 &resp, sizeof resp))
		ret = -EFAULT;

	return ret ? ret : in_len;
}
