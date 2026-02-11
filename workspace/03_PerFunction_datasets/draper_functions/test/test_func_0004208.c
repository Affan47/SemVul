hsit_enum_frame_size(struct v4l2_subdev *subdev,
				struct v4l2_subdev_pad_config *cfg,
				struct v4l2_subdev_frame_size_enum *fse)
{
	struct vsp1_hsit *hsit = to_hsit(subdev);
	struct v4l2_mbus_framefmt *format;

	format = vsp1_entity_get_pad_format(&hsit->entity, cfg, fse->pad,
					    fse->which);

	if (fse->index || fse->code != format->code)
		return -EINVAL;

	if (fse->pad == HSIT_PAD_SINK) {
		fse->min_width = HSIT_MIN_SIZE;
		fse->max_width = HSIT_MAX_SIZE;
		fse->min_height = HSIT_MIN_SIZE;
		fse->max_height = HSIT_MAX_SIZE;
	} else {


		fse->min_width = format->width;
		fse->max_width = format->width;
		fse->min_height = format->height;
		fse->max_height = format->height;
	}

	return 0;
}
