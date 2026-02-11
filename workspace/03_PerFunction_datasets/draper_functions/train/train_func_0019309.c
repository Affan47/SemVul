a3c90x_internal_SetWindow(struct INF_3C90X *inf_3c90x, int window)
{
	DBGP("a3c90x_internal_SetWindow\n");

	if (inf_3c90x->CurrentWindow == window)
		return;


	a3c90x_internal_IssueCommand(inf_3c90x->IOAddr,
				     cmdSelectRegisterWindow, window);
	inf_3c90x->CurrentWindow = window;

	return;
}
