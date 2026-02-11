s3c_camif_poll(struct file *file,
				   struct poll_table_struct *wait)
{
	struct camif_vp *vp = video_drvdata(file);
	struct camif_dev *camif = vp->camif;
	int ret;

	mutex_lock(&camif->lock);
	if (vp->owner && vp->owner != file->private_data)
		ret = -EBUSY;
	else
		ret = vb2_poll(&vp->vb_queue, file, wait);

	mutex_unlock(&camif->lock);
	return ret;
}
