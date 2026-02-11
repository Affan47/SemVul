HexString_action(Widget w _is_unused, XEvent *event, String *params, Cardinal *num_params)
{
	Cardinal i;
	int len = 0;
	char *s;
	char *t;

	action_debug(HexString_action, event, params, num_params);
	reset_idle_timer();


	for (i = 0; i < *num_params; i++) {
		t = params[i];
		if (!strncmp(t, "0x", 2) || !strncmp(t, "0X", 2))
			t += 2;
		len += strlen(t);
	}
	if (!len)
		return;


	s = Malloc(len + 1);
	*s = '\0';
	for (i = 0; i < *num_params; i++) {
		t = params[i];
		if (!strncmp(t, "0x", 2) || !strncmp(t, "0X", 2))
			t += 2;
		(void) strcat(s, t);
	}


	ps_set(s, True);
}
