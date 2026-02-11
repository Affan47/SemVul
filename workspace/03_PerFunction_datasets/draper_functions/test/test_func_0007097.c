mxr_acquire_video(struct mxr_device *mdev,
		      struct mxr_output_conf *output_conf, int output_count)
{
	struct device *dev = mdev->dev;
	struct v4l2_device *v4l2_dev = &mdev->v4l2_dev;
	int i;
	int ret = 0;
	struct v4l2_subdev *sd;

	strlcpy(v4l2_dev->name, dev_name(mdev->dev), sizeof(v4l2_dev->name));

	ret = v4l2_device_register(dev, v4l2_dev);
	if (ret) {
		mxr_err(mdev, "could not register v4l2 device.\n");
		goto fail;
	}

	mdev->alloc_ctx = vb2_dma_contig_init_ctx(mdev->dev);
	if (IS_ERR(mdev->alloc_ctx)) {
		mxr_err(mdev, "could not acquire vb2 allocator\n");
		ret = PTR_ERR(mdev->alloc_ctx);
		goto fail_v4l2_dev;
	}


	mdev->output_cnt = 0;
	for (i = 0; i < output_count; ++i) {
		struct mxr_output_conf *conf = &output_conf[i];
		struct mxr_output *out;

		sd = find_and_register_subdev(mdev, conf->module_name);

		if (sd == NULL)
			continue;
		out = kzalloc(sizeof(*out), GFP_KERNEL);
		if (out == NULL) {
			mxr_err(mdev, "no memory for '%s'\n",
				conf->output_name);
			ret = -ENOMEM;

			goto fail_output;
		}
		strlcpy(out->name, conf->output_name, sizeof(out->name));
		out->sd = sd;
		out->cookie = conf->cookie;
		mdev->output[mdev->output_cnt++] = out;
		mxr_info(mdev, "added output '%s' from module '%s'\n",
			conf->output_name, conf->module_name);

		if (mdev->output_cnt >= MXR_MAX_OUTPUTS)
			break;
	}

	if (mdev->output_cnt == 0) {
		mxr_err(mdev, "failed to register any output\n");
		ret = -ENODEV;

		goto fail_vb2_allocator;
	}

	return 0;

fail_output:

	for (i = 0; i < mdev->output_cnt; ++i)
		kfree(mdev->output[i]);
	memset(mdev->output, 0, sizeof(mdev->output));

fail_vb2_allocator:

	vb2_dma_contig_cleanup_ctx(mdev->alloc_ctx);

fail_v4l2_dev:

	v4l2_device_unregister(v4l2_dev);

fail:
	return ret;
}
