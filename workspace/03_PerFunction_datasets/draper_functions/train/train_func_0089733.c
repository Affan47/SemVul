getclass(WINDOW *w, const int row, const int state, classcode_t *exist, char *msg)
{
	char	*prompt;
	classcode_t	res;
	struct	sctrl	sc;

	sc.helpcode = state;
	sc.helpfn = HELPLESS;
	sc.size = 32;
	sc.retv = 0;
	sc.magic_p = MAG_P;
	sc.min = 0L;
	sc.vmax = U_MAX_CLASS;
	sc.msg = msg;

	prompt = gprompt(state);
	sc.col = strlen(prompt);

	wmove(w, row, 0);
	wclrtoeol(w);
	waddstr(w, prompt);
	free(prompt);
	waddstr(w, hex_disp(*exist, 1));
	res = whexnum(w, row, &sc, *exist);
	select_state(1);
	if  (res == *exist)
		return  0;
	*exist = res;
	return  1;
}
