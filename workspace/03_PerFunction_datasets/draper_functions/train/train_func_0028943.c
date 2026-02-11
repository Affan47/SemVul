collect_transients_recursive(
	FvwmWindow *t, FvwmWindow *list_head, int layer, stack_mode_t mode,
	Bool do_include_target_window)
{
	FvwmWindow *s;
	int count = 0;
	int m;

	switch (mode)
	{
	case SM_LOWER:
		m = MARK_LOWER;
		break;
	case SM_RAISE:
		m = MARK_RAISE;
		break;
	case SM_RESTACK:
		m = MARK_RESTACK;
		break;
	default:

		m = MARK_RAISE;
		break;
	}
	mark_transient_subtree(t, layer, m, True, False);

	for (s = Scr.FvwmRoot.stack_next; s != &Scr.FvwmRoot; )
	{
		FvwmWindow *tmp;

		if (s == t && do_include_target_window == False)
		{

			s = s->stack_next;
			continue;
		}
		tmp = s->stack_next;
		if (IS_IN_TRANSIENT_SUBTREE(s))
		{
			remove_window_from_stack_ring(s);
			add_window_to_stack_ring_after(
				s, list_head->stack_prev);
			count++;
			count += get_visible_icon_window_count(t);
		}
		s = tmp;
	}

	return count;
}
