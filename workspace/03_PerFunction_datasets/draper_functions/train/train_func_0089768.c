sigmadsp_ctrl_write(struct sigmadsp *sigmadsp,
	struct sigmadsp_control *ctrl, void *data)
{

	if (ctrl->num_bytes > 4 && ctrl->num_bytes <= 20 && sigmadsp->ops &&
	    sigmadsp->ops->safeload)
		return sigmadsp->ops->safeload(sigmadsp, ctrl->addr, data,
			ctrl->num_bytes);
	else
		return sigmadsp_write(sigmadsp, ctrl->addr, data,
			ctrl->num_bytes);
}
