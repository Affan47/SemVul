shuffle_update_sensitivity_cb (G_GNUC_UNUSED GtkWidget *dummy,
			       ShuffleState *state)
{
        GnmValue *input_range = gnm_expr_entry_parse_as_value (
		GNM_EXPR_ENTRY (state->input_entry), state->sheet);
	if (input_range == NULL) {
		gtk_label_set_text (GTK_LABEL (state->warning),
				    _("The input range is invalid."));
		gtk_widget_set_sensitive (state->ok_button, FALSE);
	} else {
		value_release (input_range);
		gtk_label_set_text (GTK_LABEL (state->warning), "");
		gtk_widget_set_sensitive (state->ok_button, TRUE);
	}
}
