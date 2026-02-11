ft_dump_cmd(struct ft_cmd *cmd, const char *caller)
{
	if (unlikely(ft_debug_logging))
		_ft_dump_cmd(cmd, caller);
}
