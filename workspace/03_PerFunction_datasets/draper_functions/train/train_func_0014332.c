tw9910_g_crop(struct v4l2_subdev *sd, struct v4l2_crop *a)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct tw9910_priv *priv = to_tw9910(client);

	a->c.left	= 0;
	a->c.top	= 0;
	if (priv->norm & V4L2_STD_NTSC) {
		a->c.width	= 640;
		a->c.height	= 480;
	} else {
		a->c.width	= 768;
		a->c.height	= 576;
	}
	a->type		= V4L2_BUF_TYPE_VIDEO_CAPTURE;

	return 0;
}
