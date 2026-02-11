spmi_controller_remove(struct spmi_controller *ctrl)
{
	int dummy;

	if (!ctrl)
		return;

	dummy = device_for_each_child(&ctrl->dev, NULL,
				      spmi_ctrl_remove_device);
	device_del(&ctrl->dev);
}
