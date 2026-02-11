focus_tracker_targets_received_cb (GtkClipboard *clipboard,
                                   GdkAtom *targets,
                                   gint n_targets,
                                   EFocusTracker *focus_tracker)
{
	GtkWidget *focus;

	focus = e_focus_tracker_get_focus (focus_tracker);

	if (focus == NULL)
		focus_tracker_disable_actions (focus_tracker);

	else if (GTK_IS_EDITABLE (focus))
		focus_tracker_editable_update_actions (
			focus_tracker, GTK_EDITABLE (focus),
			targets, n_targets);

	else if (E_IS_SELECTABLE (focus))
		focus_tracker_selectable_update_actions (
			focus_tracker, E_SELECTABLE (focus),
			targets, n_targets);

	g_object_unref (focus_tracker);
}
