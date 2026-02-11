v4lcontrol_vidioc_s_ctrl(struct v4lcontrol_data *data, void *arg)
{
	int i;
	struct v4l2_control *ctrl = arg;

	for (i = 0; i < V4LCONTROL_COUNT; i++)
		if ((data->controls & (1 << i)) &&
				ctrl->id == fake_controls[i].id) {
			if (ctrl->value > fake_controls[i].maximum ||
					ctrl->value < fake_controls[i].minimum) {
				errno = EINVAL;
				return -1;
			}

			data->shm_values[i] = ctrl->value;
			return 0;
		}

	return data->dev_ops->ioctl(data->dev_ops_priv, data->fd,
			VIDIOC_S_CTRL, arg);
}
