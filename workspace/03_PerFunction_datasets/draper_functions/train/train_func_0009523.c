vmmouse_disable(struct psmouse *psmouse)
{
	u32 status;
	u32 dummy1, dummy2, dummy3, dummy4;

	VMMOUSE_CMD(ABSPOINTER_COMMAND, VMMOUSE_CMD_DISABLE,
		    dummy1, dummy2, dummy3, dummy4);

	VMMOUSE_CMD(ABSPOINTER_STATUS, 0,
		    status, dummy1, dummy2, dummy3);

	if ((status & VMMOUSE_ERROR) != VMMOUSE_ERROR)
		psmouse_warn(psmouse, "failed to disable vmmouse device\n");
}
