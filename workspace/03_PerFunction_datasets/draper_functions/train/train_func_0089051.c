CMD_Resize(F_CMD_ARGS)
{
	FvwmWindow *fw = exc->w.fw;

	if (IS_EWMH_FULLSCREEN(fw))
	{

		CMD_ResizeMaximize(F_PASS_ARGS);
		return;
	}

	__resize_window(F_PASS_ARGS);

	return;
}
