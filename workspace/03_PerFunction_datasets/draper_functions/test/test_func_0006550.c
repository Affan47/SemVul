wacom_send(struct serio *serio, const u8 *command)
{
	int err = 0;

	for (; !err && *command; command++)
		err = serio_write(serio, *command);

	return err;
}
