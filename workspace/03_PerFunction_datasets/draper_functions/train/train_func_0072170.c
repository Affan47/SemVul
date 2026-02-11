mt9t001_get_selection(struct v4l2_subdev *subdev,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_selection *sel)
{
	struct mt9t001 *mt9t001 = to_mt9t001(subdev);

	if (sel->target != V4L2_SEL_TGT_CROP)
		return -EINVAL;

	sel->r = *__mt9t001_get_pad_crop(mt9t001, cfg, sel->pad, sel->which);
	return 0;
}
