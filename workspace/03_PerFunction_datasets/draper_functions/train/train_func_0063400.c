TRANS_continue(void)
{
	TRANS_CTRL *ctrl_inner = control_get_inner();

	check_try("CONTINUE");

	if (!ctrl_inner)
		THROW(E_UNEXPECTED, "CONTINUE");

	control_add_pos(&ctrl_inner->pos_continue, CODE_get_current_pos());
	CODE_jump();
}
