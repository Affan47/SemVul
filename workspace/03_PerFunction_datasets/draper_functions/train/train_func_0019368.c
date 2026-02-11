sigwinch(int signo, siginfo_t *info, void *data)
{
	struct display *display;
	for (display = display_list; display; display = display->next)
		geometry(display);
	if (old_sigwinch)
		old_sigwinch(signo, info, data);
}
