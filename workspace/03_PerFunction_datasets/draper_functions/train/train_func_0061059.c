start_screen(char *call)
{
    int cnt;

    if (initscr() == NULL)
		return -1;

    attron(A_REVERSE);
    move(0, 0);
    addstr(call);

    for (cnt = strlen(call); cnt <= 80; cnt++)
		addch(' ');

    attroff(A_REVERSE);

    noecho();
    raw();
    refresh();

    return 0;
}
