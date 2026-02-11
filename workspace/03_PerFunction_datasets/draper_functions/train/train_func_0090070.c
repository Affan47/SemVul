CloseScreen(void)
{
#ifdef HAVE_CURSES
	if (interactive == IN_CURSES)
		CloseScreenCurses();
#endif
#if defined (HAVE_GTK)
	if (interactive == IN_GTK)
		CloseScreenGTK();
#endif
}
