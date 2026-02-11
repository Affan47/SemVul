view_key_press_event_cb (GtkSourceView       *view,
			 GdkEventKey         *event,
			 GtkSourceCompletion *completion)
{
	static gboolean mnemonic_keyval_set = FALSE;
	static guint mnemonic_keyval = GDK_KEY_VoidSymbol;
	GdkModifierType mod;
	GtkBindingSet *binding_set;

	if (!gtk_widget_get_visible (GTK_WIDGET (completion->priv->main_window)))
	{
		return FALSE;
	}

	if (G_UNLIKELY (!mnemonic_keyval_set))
	{
		const gchar *label_text = gtk_button_get_label (GTK_BUTTON (completion->priv->info_button));
		GtkWidget *label = gtk_label_new_with_mnemonic (label_text);
		g_object_ref_sink (label);

		mnemonic_keyval = gtk_label_get_mnemonic_keyval (GTK_LABEL (label));
		mnemonic_keyval_set = TRUE;

		g_object_unref (label);
	}

	mod = gtk_accelerator_get_default_mod_mask () & event->state;


	if ((mod & GDK_MOD1_MASK) != 0 &&
	    event->keyval == mnemonic_keyval &&
	    gtk_widget_get_sensitive (GTK_WIDGET (completion->priv->info_button)))
	{
		gtk_toggle_button_set_active (completion->priv->info_button,
		                              !gtk_toggle_button_get_active (completion->priv->info_button));
		return TRUE;
	}

	if ((mod & GDK_MOD1_MASK) != 0 &&
	    GDK_KEY_0 <= event->keyval && event->keyval <= GDK_KEY_9)
	{
		if (activate_by_accelerator (completion, event->keyval - GDK_KEY_0))
		{
			return TRUE;
		}
	}

	binding_set = gtk_binding_set_by_class (GTK_SOURCE_COMPLETION_GET_CLASS (completion));

	if (gtk_binding_set_activate (binding_set,
	                              event->keyval,
	                              event->state,
	                              G_OBJECT (completion)))
	{
		return TRUE;
	}

	return FALSE;
}
