brasero_tool_color_picker_response (GtkWidget *widget,
                                    GtkResponseType response,
                                    BraseroToolColorPicker *self)
{
	BraseroToolColorPickerPrivate *priv;
	GtkColorSelection *selection;

	priv = BRASERO_TOOL_COLOR_PICKER_PRIVATE (self);

	if (response == GTK_RESPONSE_OK) {
		selection = GTK_COLOR_SELECTION (gtk_color_selection_dialog_get_color_selection (GTK_COLOR_SELECTION_DIALOG (priv->dialog)));
		gtk_color_selection_get_current_color (selection, &priv->color);

		g_signal_emit (self,
			       tool_color_picker_signals[COLOR_SET_SIGNAL],
			       0);
	}

	gtk_widget_destroy (priv->dialog);
	priv->dialog = NULL;
}
