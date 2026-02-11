poll_timeout(struct mlx5_cmd_work_ent *ent)
{
	unsigned long poll_end = jiffies + msecs_to_jiffies(MLX5_CMD_TIMEOUT_MSEC + 1000);
	u8 own;

	do {
		own = ent->lay->status_own;
		if (!(own & CMD_OWNER_HW)) {
			ent->ret = 0;
			return;
		}
		usleep_range(5000, 10000);
	} while (time_before(jiffies, poll_end));

	ent->ret = -ETIMEDOUT;
}
