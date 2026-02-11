alps_hw_init_v6(struct psmouse *psmouse)
{
	unsigned char param[2] = {0xC8, 0x14};


	if (alps_passthrough_mode_v2(psmouse, true))
		return -1;

	if (ps2_command(&psmouse->ps2dev, NULL, PSMOUSE_CMD_SETSCALE11) ||
	    ps2_command(&psmouse->ps2dev, NULL, PSMOUSE_CMD_SETSCALE11) ||
	    ps2_command(&psmouse->ps2dev, NULL, PSMOUSE_CMD_SETSCALE11) ||
	    ps2_command(&psmouse->ps2dev, &param[0], PSMOUSE_CMD_SETRATE) ||
	    ps2_command(&psmouse->ps2dev, &param[1], PSMOUSE_CMD_SETRATE))
		return -1;

	if (alps_passthrough_mode_v2(psmouse, false))
		return -1;

	if (alps_absolute_mode_v6(psmouse)) {
		psmouse_err(psmouse, "Failed to enable absolute mode\n");
		return -1;
	}

	return 0;
}
