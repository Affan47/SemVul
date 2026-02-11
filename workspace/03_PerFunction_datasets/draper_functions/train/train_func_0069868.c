uvc_ctrl_get(struct uvc_video_chain *chain,
	struct v4l2_ext_control *xctrl)
{
	struct uvc_control *ctrl;
	struct uvc_control_mapping *mapping;

	ctrl = uvc_find_control(chain, xctrl->id, &mapping);
	if (ctrl == NULL)
		return -EINVAL;

	return __uvc_ctrl_get(chain, ctrl, mapping, &xctrl->value);
}
