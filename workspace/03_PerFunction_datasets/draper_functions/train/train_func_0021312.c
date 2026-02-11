smiapp_pixel_order(struct smiapp_sensor *sensor)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	int flip = 0;

	if (sensor->hflip) {
		if (sensor->hflip->val)
			flip |= SMIAPP_IMAGE_ORIENTATION_HFLIP;

		if (sensor->vflip->val)
			flip |= SMIAPP_IMAGE_ORIENTATION_VFLIP;
	}

	flip ^= sensor->hvflip_inv_mask;

	dev_dbg(&client->dev, "flip %d\n", flip);
	return sensor->default_pixel_order ^ flip;
}
