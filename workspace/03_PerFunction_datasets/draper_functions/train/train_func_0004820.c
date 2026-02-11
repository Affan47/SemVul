readline(const char *prompt)
{
    char *line;


    rl_initialize();

    if (!isatty(0)) {
        tty_flush();
        return read_redirected();
    }

    if (!rl_line_buffer) {
        Length = MEM_INC;
	rl_line_buffer = malloc(sizeof(char) * Length);
        if (!rl_line_buffer)
            return NULL;
    }

    tty_info();
    rl_prep_term_function(!rl_meta_chars);
    hist_add(NILSTR);
    ScreenSize = SCREEN_INC;
    Screen = malloc(sizeof(char) * ScreenSize);
    if (!Screen)
	return NULL;

    rl_prompt = prompt ? prompt : NILSTR;
    if (el_no_echo) {
	int old = el_no_echo;
	el_no_echo = 0;
	tty_puts(rl_prompt);
	tty_flush();
	el_no_echo = old;
    } else {
	tty_puts(rl_prompt);
    }

    line = editinput();
    if (line) {
        line = strdup(line);
        tty_puts(NEWLINE);
        tty_flush();
    }

    rl_deprep_term_function();
    free(Screen);
    free(H.Lines[--H.Size]);


    if (!el_no_echo) {
	if (line != NULL && *line != '\0')
	    hist_add(line);
    }

    if (el_intr_pending > 0) {
	int s = el_intr_pending;
        el_intr_pending = 0;
        kill(getpid(), s);
    }

    return line;
}
