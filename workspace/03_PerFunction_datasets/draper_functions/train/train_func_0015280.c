focus_does_accept_input_focus(const FvwmWindow *fw)
{
	return (!fw || !fw->wmhints ||
		!(fw->wmhints->flags & InputHint) || fw->wmhints->input);
}
