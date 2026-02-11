reposition(void)
{
    int         i;
    char        *p;

    tty_put('\r');
    tty_puts(Prompt);
    for (i = Point, p = Line; --i >= 0; p++)
        tty_show(*p);
}
