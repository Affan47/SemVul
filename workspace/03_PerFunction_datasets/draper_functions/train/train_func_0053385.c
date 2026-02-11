sigmadsp_reset(struct sigmadsp *sigmadsp)
{
	struct sigmadsp_control *ctrl;

	list_for_each_entry(ctrl, &sigmadsp->ctrl_list, head)
		sigmadsp_activate_ctrl(sigmadsp, ctrl, false);

	sigmadsp->current_samplerate = 0;
}
