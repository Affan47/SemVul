saa711x_g_vbi_data(struct v4l2_subdev *sd, struct v4l2_sliced_vbi_data *data)
{


	switch (data->id) {
	case V4L2_SLICED_WSS_625:
		if (saa711x_read(sd, 0x6b) & 0xc0)
			return -EIO;
		data->data[0] = saa711x_read(sd, 0x6c);
		data->data[1] = saa711x_read(sd, 0x6d);
		return 0;
	case V4L2_SLICED_CAPTION_525:
		if (data->field == 0) {

			if (saa711x_read(sd, 0x66) & 0x30)
				return -EIO;
			data->data[0] = saa711x_read(sd, 0x69);
			data->data[1] = saa711x_read(sd, 0x6a);
			return 0;
		}

		if (saa711x_read(sd, 0x66) & 0xc0)
			return -EIO;
		data->data[0] = saa711x_read(sd, 0x67);
		data->data[1] = saa711x_read(sd, 0x68);
		return 0;
	default:
		return -EINVAL;
	}
}
