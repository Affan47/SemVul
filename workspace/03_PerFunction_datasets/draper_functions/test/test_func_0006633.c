mxr_video_open(struct file *file)
{
	struct mxr_layer *layer = video_drvdata(file);
	struct mxr_device *mdev = layer->mdev;
	int ret = 0;

	mxr_dbg(mdev, "%s:%d\n", __func__, __LINE__);
	if (mutex_lock_interruptible(&layer->mutex))
		return -ERESTARTSYS;

	wait_for_device_probe();

	ret = v4l2_fh_open(file);
	if (ret) {
		mxr_err(mdev, "v4l2_fh_open failed\n");
		goto unlock;
	}


	if (!v4l2_fh_is_singular_file(file))
		goto unlock;


	ret = mxr_power_get(mdev);
	if (ret) {
		mxr_err(mdev, "power on failed\n");
		goto fail_fh_open;
	}

	ret = vb2_queue_init(&layer->vb_queue);
	if (ret != 0) {
		mxr_err(mdev, "failed to initialize vb2 queue\n");
		goto fail_power;
	}

	layer->fmt = layer->fmt_array[0];

	mxr_layer_default_geo(layer);
	mutex_unlock(&layer->mutex);

	return 0;

fail_power:
	mxr_power_put(mdev);

fail_fh_open:
	v4l2_fh_release(file);

unlock:
	mutex_unlock(&layer->mutex);

	return ret;
}
