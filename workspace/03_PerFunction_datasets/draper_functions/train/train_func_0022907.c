KeysBoxCurses(void)
{


	alarm(0);
	timeout(-1);
	in_keysbox = TRUE;
	clear();
	attrset(COLOR_PAIR(AXIS_COLOR));
	move(3, 0);
	addstr((char *) LOCAL_TEXT("page arrows\n"));
	addstr((char *) LOCAL_TEXT("tab enter < > , .\n"));
	addstr((char *) LOCAL_TEXT("+ - [ ] arrows digits\n"));
	addstr((char *) LOCAL_TEXT("space\n"));
	addstr((char *) LOCAL_TEXT("|\n"));
	printw((char *) LOCAL_TEXT("\nPress a key or mouse button to resume."));
	move(1, 0);
	printw((char *) LOCAL_TEXT("Key                       Function\n"));
	printw((char *) LOCAL_TEXT("------------------------- --------------------"));
	mvaddstr(3, 26, (char *) LOCAL_TEXT("change channel\n"));
	mvaddstr(4, 26, (char *) LOCAL_TEXT("toggle level/balance\n"));
	mvaddstr(5, 26, (char *) LOCAL_TEXT("adjust slider\n"));
	mvaddstr(6, 26, (char *) LOCAL_TEXT("toggle record/play\n"));
	mvaddstr(7, 26, (char *) LOCAL_TEXT("center balance\n"));
	refresh();

	Getch();
	alarm(REFRESH_PERIOD);
	in_keysbox = FALSE;
	timeout(1000);
	clear();
	InitScreen();
	DrawLevelBalModeCurses(current_dev, levelbalmode);
	HighlightLabelCurses();
}
