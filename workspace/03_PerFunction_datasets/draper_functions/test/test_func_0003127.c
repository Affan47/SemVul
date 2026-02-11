get_check(const char *prompt)
{

	ui_event ke;

	char buf[80];

	bool repeat = FALSE;


	message_flush();


	strnfmt(buf, 78, "%.70s[y/n] ", prompt);


	if (button_kill('n')) repeat = TRUE;


	button_add("[y]", 'y');
	button_add("[n]", 'n');
	redraw_stuff(p_ptr);


	prt(buf, 0, 0);
	ke = inkey_m();


	button_kill('y');
	button_kill('n');


	if (repeat) button_add("[Rpt]", 'n');
	redraw_stuff(p_ptr);


	prt("", 0, 0);


	if (ke.type == EVT_MOUSE) {
		if ((ke.mouse.button != 1) && (ke.mouse.y != 0)) return (FALSE);
	} else
	if ((ke.key.code != 'Y') && (ke.key.code != 'y')) return (FALSE);


	return (TRUE);
}
