get_current_win(void)
{
	Button *b = function_context.current_button;

	if (b && b->drawn_state.win)
	{
		return b->drawn_state.win;
	}
	return NULL;
}
