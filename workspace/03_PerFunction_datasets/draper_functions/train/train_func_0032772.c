data_radio_toggled_cb (glObjectEditor *editor)
{
        gl_debug (DEBUG_WDGT, "START");

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (editor->priv->data_literal_radio))) {
                gtk_widget_set_sensitive (editor->priv->data_text_entry, TRUE);
                gtk_widget_set_sensitive (editor->priv->data_key_combo, FALSE);
		gtk_widget_set_sensitive (editor->priv->data_format_label, FALSE);
		gtk_widget_set_sensitive (editor->priv->data_ex_label, FALSE);
		gtk_widget_set_sensitive (editor->priv->data_digits_label, FALSE);
		gtk_widget_set_sensitive (editor->priv->data_digits_spin, FALSE);
        } else {
                gtk_widget_set_sensitive (editor->priv->data_text_entry, FALSE);
                gtk_widget_set_sensitive (editor->priv->data_key_combo, TRUE);
		gtk_widget_set_sensitive (editor->priv->data_format_label, TRUE);
		gtk_widget_set_sensitive (editor->priv->data_ex_label, TRUE);
		gtk_widget_set_sensitive (editor->priv->data_digits_label,
					  !editor->priv->data_format_fixed_flag);
		gtk_widget_set_sensitive (editor->priv->data_digits_spin,
					  !editor->priv->data_format_fixed_flag);
	}

        gl_object_editor_changed_cb (editor);

        gl_debug (DEBUG_WDGT, "END");
}
