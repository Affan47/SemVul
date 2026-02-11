popup_action_set_use_action_appearance (EPopupAction *popup_action,
                                        gboolean use_action_appearance)
{
	GtkActivatable *activatable;
	GtkAction *related_action;

	if (popup_action->priv->use_action_appearance == use_action_appearance)
		return;

	popup_action->priv->use_action_appearance = use_action_appearance;

	g_object_notify (G_OBJECT (popup_action), "use-action-appearance");

	activatable = GTK_ACTIVATABLE (popup_action);
	related_action = popup_action_get_related_action (popup_action);
	gtk_activatable_sync_action_properties (activatable, related_action);
}
