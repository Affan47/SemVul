ps2_end_command(struct ps2dev *ps2dev)
{
	struct mutex *m = ps2dev->serio->ps2_cmd_mutex ?: &ps2dev->cmd_mutex;

	mutex_unlock(m);
}
