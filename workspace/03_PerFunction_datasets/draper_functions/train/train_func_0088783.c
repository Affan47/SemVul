readline(const char *prompt)
{
    char        *line;
    int         s;


    rl_initialize ();

    if (!isatty(0)) {
        tty_flush();
        return read_redirected();
    }

    if (Line == NULL) {
        Length = MEM_INC;
        if ((Line = NEW(char, Length)) == NULL)
            return NULL;
    }

    tty_info();
    rl_ttyset(0);
    hist_add(NIL);
    ScreenSize = SCREEN_INC;
    Screen = NEW(char, ScreenSize);
    Prompt = prompt ? prompt : NIL;
    tty_puts(Prompt);
    if ((line = editinput()) != NULL) {
        line = strdup(line);
        tty_puts(NEWLINE);
        tty_flush();
    }
    rl_ttyset(1);
    DISPOSE(Screen);
    DISPOSE(H.Lines[--H.Size]);

    if (line != NULL && *line != '\0'
#if     defined(UNIQUE_HISTORY)
        && !(H.Pos && strcmp((char *) line, (char *) H.Lines[H.Pos - 1]) == 0)
#endif
        && !(H.Size && strcmp((char *) line, (char *) H.Lines[H.Size - 1]) == 0)
    ) {
        hist_add(line);
    }

    if (Signal > 0) {
        s = Signal;
        Signal = 0;
        (void)kill(getpid(), s);
    }
    return (char *)line;
}
