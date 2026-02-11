quit(int sig)


{
    int ch;
    void (*osig)() = signal(SIGINT, SIG_IGN);
    (void) signal(SIGQUIT, SIG_IGN);

    if (stdscr) {
	botmsg("Really quit? ", false);
	if ((ch = getch()) != 'y' && ch != 'Y') {
	    move(y, x);
	    (void) signal(SIGINT, osig);
	    (void) signal(SIGQUIT, osig);
	    refresh();
	    return;
	}
	move(23, 0);
	refresh();
	endwin();
	puts("\n");
	topscores(score);
    }
    exit(0);
}
