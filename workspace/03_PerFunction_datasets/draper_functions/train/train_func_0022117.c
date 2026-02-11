ceol(void)
{
    int         extras;
    int         i;
    char        *p;

    for (extras = 0, i = Point, p = &Line[i]; i <= End; i++, p++) {
        tty_put(' ');
        if (ISCTL(*p)) {
            tty_put(' ');
            extras++;
        }
        else if (rl_meta_chars && ISMETA(*p)) {
            tty_put(' ');
            tty_put(' ');
            extras += 2;
        }
    }

    for (i += extras; i > Point; i--)
        tty_back();
}
