mxr_s_output(struct file *file, void *fh, unsigned int i)
{
	struct video_device *vfd = video_devdata(file);
	struct mxr_layer *layer = video_drvdata(file);
	struct mxr_device *mdev = layer->mdev;

	if (i >= mdev->output_cnt || mdev->output[i] == NULL)
		return -EINVAL;

	mutex_lock(&mdev->mutex);
	if (mdev->n_output > 0) {
		mutex_unlock(&mdev->mutex);
		return -EBUSY;
	}
	mdev->current_output = i;
	vfd->tvnorms = 0;
	v4l2_subdev_call(to_outsd(mdev), video, g_tvnorms_output,
		&vfd->tvnorms);
	mutex_unlock(&mdev->mutex);


	mxr_layer_update_output(layer);

	mxr_dbg(mdev, "tvnorms = %08llx\n", vfd->tvnorms);

	return 0;
}
