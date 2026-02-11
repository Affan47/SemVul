panel_ditem_editor_activated (PanelDItemEditor *dialog)
{
	if (gtk_widget_get_visible (dialog->priv->ok_button))
		gtk_dialog_response (GTK_DIALOG (dialog),
				     GTK_RESPONSE_OK);
	else if (gtk_widget_get_visible (dialog->priv->close_button))
		gtk_dialog_response (GTK_DIALOG (dialog),
				     GTK_RESPONSE_CLOSE);
}
