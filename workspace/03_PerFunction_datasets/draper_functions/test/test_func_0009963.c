m5mols_start_monitor(struct m5mols_info *info)
{
	struct v4l2_subdev *sd = &info->sd;
	int ret;

	ret = m5mols_set_mode(info, REG_PARAMETER);
	if (!ret)
		ret = m5mols_write(sd, PARM_MON_SIZE, info->resolution);
	if (!ret)
		ret = m5mols_write(sd, PARM_MON_FPS, REG_FPS_30);
	if (!ret)
		ret = m5mols_set_mode(info, REG_MONITOR);
	if (!ret)
		ret = m5mols_restore_controls(info);

	return ret;
}
