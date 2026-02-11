get_check(const char *prompt)
{
	struct keypress ke;

	char buf[80];

	bool repeat = FALSE;


	message_flush();


	strnfmt(buf, 78, "%.70s[y/n] ", prompt);


	if (button_kill('n')) repeat = TRUE;


	button_add("[y]", 'y');
	button_add("[n]", 'n');
	redraw_stuff(p_ptr);


	prt(buf, 0, 0);
	ke = inkey();


	button_kill('y');
	button_kill('n');


	if (repeat) button_add("[Rpt]", 'n');
	redraw_stuff(p_ptr);


	prt("", 0, 0);


	if ((ke.code != 'Y') && (ke.code != 'y')) return (FALSE);


	return (TRUE);
}
