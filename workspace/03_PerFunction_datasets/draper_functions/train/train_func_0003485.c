control_get_inner(void)
{
	int level = ctrl_level;
	TRANS_CTRL *ctrl_look;

	for(;;)
	{
		if (!level)
			return NULL;

		level--;
		ctrl_look = &ctrl_data[level];

		if ((ctrl_look->type == RS_DO)
				|| (ctrl_look->type == RS_WHILE)
				|| (ctrl_look->type == RS_REPEAT)
				|| (ctrl_look->type == RS_FOR)
				|| (ctrl_look->type == RS_EACH))
			return ctrl_look;
	}
}
