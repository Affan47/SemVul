brasero_dest_selection_medium_changed (BraseroMediumSelection *selection,
				       BraseroMedium *medium)
{
	BraseroDestSelectionPrivate *priv;

	priv = BRASERO_DEST_SELECTION_PRIVATE (selection);

	if (!priv->session)
		goto chain;

	if (!medium) {
	    	gtk_widget_set_sensitive (GTK_WIDGET (selection), FALSE);
		goto chain;
	}

	if (brasero_medium_get_drive (medium) == brasero_burn_session_get_burner (priv->session))
		goto chain;

	if (priv->locked_drive && priv->locked_drive != brasero_medium_get_drive (medium)) {
		brasero_medium_selection_set_active (selection, medium);
		goto chain;
	}

	brasero_burn_session_set_burner (priv->session, brasero_medium_get_drive (medium));
	gtk_widget_set_sensitive (GTK_WIDGET (selection), (priv->locked_drive == NULL));

chain:

	if (BRASERO_MEDIUM_SELECTION_CLASS (brasero_dest_selection_parent_class)->medium_changed)
		BRASERO_MEDIUM_SELECTION_CLASS (brasero_dest_selection_parent_class)->medium_changed (selection, medium);
}
