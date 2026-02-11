ivtv_v4l2_read(struct file * filp, char __user *buf, size_t count, loff_t * pos)
{
	struct ivtv_open_id *id = fh2id(filp->private_data);
	struct ivtv *itv = id->itv;
	struct ivtv_stream *s = &itv->streams[id->type];
	ssize_t rc;

	IVTV_DEBUG_HI_FILE("read %zd bytes from %s\n", count, s->name);

	if (mutex_lock_interruptible(&itv->serialize_lock))
		return -ERESTARTSYS;
	rc = ivtv_start_capture(id);
	if (!rc)
		rc = ivtv_read_pos(s, buf, count, pos, filp->f_flags & O_NONBLOCK);
	mutex_unlock(&itv->serialize_lock);
	return rc;
}
