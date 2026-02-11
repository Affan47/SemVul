gog_tool_action_move (GogToolAction *action, double x, double y)
{
	g_return_if_fail (action != NULL);

	if (action->tool->move != NULL)
		(action->tool->move) (action, x, y);
}
