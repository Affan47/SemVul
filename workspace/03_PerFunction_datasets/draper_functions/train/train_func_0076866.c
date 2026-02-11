mt9m001_s_fmt(struct v4l2_subdev *sd,
			 struct v4l2_mbus_framefmt *mf)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9m001 *mt9m001 = to_mt9m001(client);
	struct v4l2_crop a = {
		.c = {
			.left	= mt9m001->rect.left,
			.top	= mt9m001->rect.top,
			.width	= mf->width,
			.height	= mf->height,
		},
	};
	int ret;


	ret = mt9m001_s_crop(sd, &a);
	if (!ret) {
		mf->width	= mt9m001->rect.width;
		mf->height	= mt9m001->rect.height;
		mt9m001->fmt	= mt9m001_find_datafmt(mf->code,
					mt9m001->fmts, mt9m001->num_fmts);
		mf->colorspace	= mt9m001->fmt->colorspace;
	}

	return ret;
}
