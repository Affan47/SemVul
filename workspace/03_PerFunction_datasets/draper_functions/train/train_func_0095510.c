timblogiw_s_fmt(struct file *file, void  *priv,
	struct v4l2_format *format)
{
	struct video_device *vdev = video_devdata(file);
	struct timblogiw *lw = video_get_drvdata(vdev);
	struct timblogiw_fh *fh = priv;
	struct v4l2_pix_format *pix = &format->fmt.pix;
	int err;

	mutex_lock(&lw->lock);

	err = timblogiw_try_fmt(file, priv, format);
	if (err)
		goto out;

	if (videobuf_queue_is_busy(&fh->vb_vidq)) {
		dev_err(&vdev->dev, "%s queue busy\n", __func__);
		err = -EBUSY;
		goto out;
	}

	pix->width = fh->cur_norm->width;
	pix->height = fh->cur_norm->height;

out:
	mutex_unlock(&lw->lock);
	return err;
}
