w1_process_command_slave(struct w1_slave *sl,
		struct w1_netlink_cmd *cmd)
{
	dev_dbg(&sl->master->dev, "%s: %02x.%012llx.%02x: cmd=%02x, len=%u.\n",
		__func__, sl->reg_num.family, (unsigned long long)sl->reg_num.id,
		sl->reg_num.crc, cmd->cmd, cmd->len);

	return w1_process_command_io(sl->master, cmd);
}
