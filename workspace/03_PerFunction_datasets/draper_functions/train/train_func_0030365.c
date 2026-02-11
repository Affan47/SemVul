brasero_medium_properties_output_changed (BraseroBurnSession *session,
					  BraseroMedium *former,
					  BraseroMediumProperties *self)
{
	BraseroMediumPropertiesPrivate *priv;
	BraseroDrive *burner;

	priv = BRASERO_MEDIUM_PROPERTIES_PRIVATE (self);


	burner = brasero_burn_session_get_burner (session);
	if (former == brasero_drive_get_medium (burner))
		return;


	if (priv->medium_prop) {
		gtk_dialog_response (GTK_DIALOG (priv->medium_prop),
				     GTK_RESPONSE_CANCEL);
		priv->medium_prop = NULL;
	}
}
