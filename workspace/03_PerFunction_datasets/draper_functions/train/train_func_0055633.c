handle_stick_across_pages(
	F_CMD_ARGS, int toggle, int do_not_draw, int do_silently)
{
	FvwmWindow *fw = exc->w.fw;
	int did_change;

	did_change = stick_across_pages(F_PASS_ARGS, toggle);
	if (did_change)
	{
		__handle_stick_exit(fw, do_not_draw, do_silently);
	}

	return;
}
