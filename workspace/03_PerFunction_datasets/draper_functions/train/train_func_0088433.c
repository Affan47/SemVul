__try_program_focus(Window w, const FvwmWindow *fw)
{
	if (fw && WM_TAKES_FOCUS(fw) &&
	    FP_DO_FOCUS_BY_PROGRAM(FW_FOCUS_POLICY(fw)))
	{
		send_clientmessage(dpy, w, _XA_WM_TAKE_FOCUS, fev_get_evtime());
	}

	return;
}
