s3c_camif_open(struct file *file)
{
	struct camif_vp *vp = video_drvdata(file);
	struct camif_dev *camif = vp->camif;
	int ret;

	pr_debug("[vp%d] state: %#x,  owner: %p, pid: %d\n", vp->id,
		 vp->state, vp->owner, task_pid_nr(current));

	if (mutex_lock_interruptible(&camif->lock))
		return -ERESTARTSYS;

	ret = v4l2_fh_open(file);
	if (ret < 0)
		goto unlock;

	ret = pm_runtime_get_sync(camif->dev);
	if (ret < 0)
		goto err_pm;

	ret = sensor_set_power(camif, 1);
	if (!ret)
		goto unlock;

	pm_runtime_put(camif->dev);
err_pm:
	v4l2_fh_release(file);
unlock:
	mutex_unlock(&camif->lock);
	return ret;
}
