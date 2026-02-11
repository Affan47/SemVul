vmmouse_reconnect(struct psmouse *psmouse)
{
	int error;

	psmouse_reset(psmouse);
	vmmouse_disable(psmouse);
	error = vmmouse_enable(psmouse);
	if (error) {
		psmouse_err(psmouse,
			    "Unable to re-enable mouse when reconnecting, err: %d\n",
			    error);
		return error;
	}

	return 0;
}
