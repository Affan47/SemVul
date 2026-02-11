alps_passthrough_mode_v2(struct psmouse *psmouse, bool enable)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	int cmd = enable ? PSMOUSE_CMD_SETSCALE21 : PSMOUSE_CMD_SETSCALE11;

	if (ps2_command(ps2dev, NULL, cmd) ||
	    ps2_command(ps2dev, NULL, cmd) ||
	    ps2_command(ps2dev, NULL, cmd) ||
	    ps2_command(ps2dev, NULL, PSMOUSE_CMD_DISABLE))
		return -1;


	ps2_drain(ps2dev, 3, 100);

	return 0;
}
