uvc_ctrl_init_ctrl(struct uvc_device *dev, struct uvc_control *ctrl)
{
	const struct uvc_control_info *info = uvc_ctrls;
	const struct uvc_control_info *iend = info + ARRAY_SIZE(uvc_ctrls);
	const struct uvc_control_mapping *mapping = uvc_ctrl_mappings;
	const struct uvc_control_mapping *mend =
		mapping + ARRAY_SIZE(uvc_ctrl_mappings);


	if (UVC_ENTITY_TYPE(ctrl->entity) == UVC_VC_EXTENSION_UNIT)
		return;

	for (; info < iend; ++info) {
		if (uvc_entity_match_guid(ctrl->entity, info->entity) &&
		    ctrl->index == info->index) {
			uvc_ctrl_add_info(dev, ctrl, info);
			break;
		 }
	}

	if (!ctrl->initialized)
		return;

	for (; mapping < mend; ++mapping) {
		if (uvc_entity_match_guid(ctrl->entity, mapping->entity) &&
		    ctrl->info.selector == mapping->selector)
			__uvc_ctrl_add_mapping(dev, ctrl, mapping);
	}
}
