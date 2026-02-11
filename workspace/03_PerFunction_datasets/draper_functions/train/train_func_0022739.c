vsp1_entity_get_pad_format(struct vsp1_entity *entity,
			   struct v4l2_subdev_pad_config *cfg,
			   unsigned int pad, u32 which)
{
	switch (which) {
	case V4L2_SUBDEV_FORMAT_TRY:
		return v4l2_subdev_get_try_format(&entity->subdev, cfg, pad);
	case V4L2_SUBDEV_FORMAT_ACTIVE:
		return &entity->formats[pad];
	default:
		return NULL;
	}
}
