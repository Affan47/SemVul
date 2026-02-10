_e2_pane_focus_action (gpointer from, E2_ActionRuntime *art)
{
	E2_PaneRuntime *rt = (E2_PaneRuntime *)art->action->data;
	if (rt != NULL && rt != curr_pane)
	{
		e2_pane_activate_other ();
		return TRUE;
	}
	else if (rt == NULL)
	{
		gtk_widget_grab_focus (curr_view->treeview);
		return TRUE;
	}
	return FALSE;
}
