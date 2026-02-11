alps_exit_command_mode(struct psmouse *psmouse)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	if (ps2_command(ps2dev, NULL, PSMOUSE_CMD_SETSTREAM))
		return -1;
	return 0;
}
