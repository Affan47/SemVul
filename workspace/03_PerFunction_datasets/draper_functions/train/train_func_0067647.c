__mark_group_member(
	FvwmWindow *fw, FvwmWindow *start, FvwmWindow *end)
{
	FvwmWindow *t;

	for (t = start; t != end; t = t->stack_next)
	{
		if (FW_W(t) == fw->wmhints->window_group ||
		    (t->wmhints && (t->wmhints->flags & WindowGroupHint) &&
		     t->wmhints->window_group == fw->wmhints->window_group))
		{
			if (IS_IN_TRANSIENT_SUBTREE(t))
			{

				SET_IN_TRANSIENT_SUBTREE(fw, 1);
			}
		}
	}

	return;

}
