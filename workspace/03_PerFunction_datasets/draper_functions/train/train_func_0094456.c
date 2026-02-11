nemo_window_pane_dispose (GObject *object)
{
	NemoWindowPane *pane = NEMO_WINDOW_PANE (object);

	unset_focus_widget (pane);

	pane->window = NULL;
	g_clear_object (&pane->action_group);

	g_assert (pane->slots == NULL);

	G_OBJECT_CLASS (nemo_window_pane_parent_class)->dispose (object);
}
