bl_pipe_destroy_msg(struct rpc_pipe_msg *msg)
{
	struct bl_pipe_msg *bl_pipe_msg =
		container_of(msg, struct bl_pipe_msg, msg);

	if (msg->errno >= 0)
		return;
	wake_up(bl_pipe_msg->bl_wq);
}
