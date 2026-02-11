panel_applet_bindings_key_event_is_binding (GdkEventKey *event,
					    GType        type,
					    const char  *signal_name,
					    gboolean    *is_popup,
					    gboolean    *is_popup_modifier)
{
	GtkBindingSet   *binding_set;
	GtkBindingEntry *binding_entry;
	gboolean         popup = FALSE;
	gboolean         popup_modifier = FALSE;
	guint            modifiers;
	char            *signal_dash;
	char            *signal_underscore;

	modifiers = event->state & gtk_accelerator_get_default_mod_mask ();

	signal_dash = g_strdup (signal_name);
	g_strdelimit (signal_dash, "_", '-');
	signal_underscore = g_strdup (signal_name);
	g_strdelimit (signal_underscore, "-", '_');

	binding_set = gtk_binding_set_by_class (g_type_class_peek (type));

	for (binding_entry = binding_set->entries;
	     binding_entry != NULL;
	     binding_entry = binding_entry->set_next) {
		GtkBindingSignal *binding_signal;

		for (binding_signal = binding_entry->signals;
		     binding_signal != NULL;
		     binding_signal = binding_signal->next) {
			if (g_strcmp0 (binding_signal->signal_name, signal_dash) == 0 ||
			    g_strcmp0 (binding_signal->signal_name, signal_underscore) == 0) {
				if (binding_entry->keyval != event->keyval)
					break;

				popup = modifiers == binding_entry->modifiers;
				popup_modifier = modifiers == (panel_applet_bindings_get_mouse_button_modifier_keymask ()|binding_entry->modifiers);
				break;
			}
		}

		if (popup || popup_modifier)
			break;
	}

	if (is_popup)
		*is_popup = popup;
	if (is_popup_modifier)
		*is_popup_modifier = popup_modifier;

	g_free (signal_dash);
	g_free (signal_underscore);
}
