GetMove(int *From, int *To)
{
    mvaddstr(STATUSLINE, 0, "Next move ('q' to quit) from ");
    clrtoeol();
    refresh();
    if ((*From = getch()) == 'q')
	return TRUE;
    *From -= ('0' + 1);
    addstr(" to ");
    clrtoeol();
    refresh();

    if ((*To = getch()) == 'q')
	return TRUE;
    *To -= ('0' + 1);
    refresh();
    if (!AutoFlag)
	napms(500);

    move(STATUSLINE, 0);
    clrtoeol();
    refresh();
    return FALSE;
}
