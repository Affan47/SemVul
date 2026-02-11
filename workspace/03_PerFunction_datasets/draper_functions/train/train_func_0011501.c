rl_initialize(void)
{
	HistEvent ev;
	int editmode = 1;
	struct termios t;

	if (e != NULL)
		el_end(e);
	if (h != NULL)
		history_end(h);

	if (!rl_instream)
		rl_instream = stdin;
	if (!rl_outstream)
		rl_outstream = stdout;


	if (tcgetattr(fileno(rl_instream), &t) != -1 && (t.c_lflag & ECHO) == 0)
		editmode = 0;

	e = el_init(rl_readline_name, rl_instream, rl_outstream, stderr);

	if (!editmode)
		el_set(e, EL_EDITMODE, 0);

	h = history_init();
	if (!e || !h)
		return -1;

	history(h, &ev, H_SETSIZE, INT_MAX);
	history_length = 0;
	max_input_history = INT_MAX;
	el_set(e, EL_HIST, history, h);


	el_set(e, EL_RESIZE, _resize_fun, &rl_line_buffer);


	if (rl_getc_function)
		el_set(e, EL_GETCFN, _getc_function);


	if (rl_set_prompt("") == -1) {
		history_end(h);
		el_end(e);
		return -1;
	}
	el_set(e, EL_PROMPT, _get_prompt, RL_PROMPT_START_IGNORE);
	el_set(e, EL_SIGNAL, rl_catch_signals);


	el_set(e, EL_EDITOR, "emacs");
	if (rl_terminal_name != NULL)
		el_set(e, EL_TERMINAL, rl_terminal_name);
	else
		el_get(e, EL_TERMINAL, &rl_terminal_name);


	el_set(e, EL_ADDFN, "rl_complete",
	    "ReadLine compatible completion function",
	    _el_rl_complete);
	el_set(e, EL_BIND, "^I", "rl_complete", NULL);


	el_set(e, EL_ADDFN, "rl_tstp",
	    "ReadLine compatible suspend function",
	    _el_rl_tstp);
	el_set(e, EL_BIND, "^Z", "rl_tstp", NULL);


	el_source(e, NULL);


	_resize_fun(e, &rl_line_buffer);
	_rl_update_pos();

	if (rl_startup_hook)
		(*rl_startup_hook)(NULL, 0);

	return 0;
}
