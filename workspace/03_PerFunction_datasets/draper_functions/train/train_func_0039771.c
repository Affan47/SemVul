alps_monitor_mode_write_reg(struct psmouse *psmouse,
				       u16 addr, u16 value)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;


	if (ps2_command(ps2dev, NULL, PSMOUSE_CMD_ENABLE) ||
	    alps_monitor_mode_send_word(psmouse, 0x0A0) ||
	    alps_monitor_mode_send_word(psmouse, addr) ||
	    alps_monitor_mode_send_word(psmouse, value) ||
	    ps2_command(ps2dev, NULL, PSMOUSE_CMD_DISABLE))
		return -1;

	return 0;
}
