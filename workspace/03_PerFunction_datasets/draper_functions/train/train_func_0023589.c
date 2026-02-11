viacam_streamon(struct file *filp, void *priv, enum v4l2_buf_type t)
{
	struct via_camera *cam = priv;
	int ret = 0;

	if (t != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	mutex_lock(&cam->lock);
	if (cam->opstate != S_IDLE) {
		ret = -EBUSY;
		goto out;
	}


	if (cam->owner && cam->owner != filp) {
		ret = -EBUSY;
		goto out;
	}
	cam->owner = filp;


	if (test_bit(CF_CONFIG_NEEDED, &cam->flags)) {
		ret = viacam_configure_sensor(cam);
		if (ret)
			goto out;
		ret = viacam_config_controller(cam);
		if (ret)
			goto out;
	}


	pm_qos_add_request(&cam->qos_request, PM_QOS_CPU_DMA_LATENCY, 50);


	INIT_LIST_HEAD(&cam->buffer_queue);
	ret = videobuf_streamon(&cam->vb_queue);
	if (!ret)
		viacam_start_engine(cam);
out:
	mutex_unlock(&cam->lock);
	return ret;
}
