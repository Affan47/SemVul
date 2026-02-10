get_queue_member_status(struct member *cur)
{
	return ast_strlen_zero(cur->state_exten) ? ast_device_state(cur->state_interface) : extensionstate2devicestate(ast_extension_state(NULL, cur->state_context, cur->state_exten));
}
