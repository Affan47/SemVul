mei_amthif_host_init(struct mei_device *dev, struct mei_me_client *me_cl)
{
	struct mei_cl *cl = &dev->iamthif_cl;
	int ret;

	dev->iamthif_state = MEI_IAMTHIF_IDLE;

	mei_cl_init(cl, dev);

	ret = mei_cl_link(cl, MEI_IAMTHIF_HOST_CLIENT_ID);
	if (ret < 0) {
		dev_err(dev->dev, "amthif: failed cl_link %d\n", ret);
		return ret;
	}

	ret = mei_cl_connect(cl, me_cl, NULL);

	dev->iamthif_state = MEI_IAMTHIF_IDLE;

	return ret;
}
