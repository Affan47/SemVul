inst_select_inst(struct inst *inst)
{
	selected_inst = inst;
	tool_selected_inst(inst);
	gui_frame_select_inst(inst);
	if (inst->ops->select)
		selected_inst->ops->select(inst);
	status_set_icon(get_icon_by_inst(inst));
}
