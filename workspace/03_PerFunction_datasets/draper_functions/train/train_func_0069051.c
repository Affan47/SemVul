res_get(struct em28xx *dev, enum v4l2_buf_type f_type)
{
	int res_type = get_ressource(f_type);


	if (dev->resources & res_type) {

		return -EBUSY;
	}


	dev->resources |= res_type;
	em28xx_videodbg("res: get %d\n", res_type);
	return 0;
}
