update_and_emit (CEPolkitButton *self, gboolean old_actionable)
{
	gboolean new_actionable;

	new_actionable = ce_polkit_button_get_actionable (self);
	update_button (self, new_actionable);
	if (new_actionable != old_actionable)
		g_signal_emit (self, signals[ACTIONABLE], 0, new_actionable);
}
