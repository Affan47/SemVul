brasero_drive_selection_set_active (BraseroDriveSelection *selector,
				     BraseroDrive *drive)
{
	BraseroDriveSelectionPrivate *priv;
	gboolean result = FALSE;
	GtkTreeModel *model;
	GtkTreeIter iter;

	g_return_val_if_fail (selector != NULL, FALSE);
	g_return_val_if_fail (BRASERO_IS_DRIVE_SELECTION (selector), FALSE);

	priv = BRASERO_DRIVE_SELECTION_PRIVATE (selector);

	if (priv->active == drive)
		return TRUE;

	model = gtk_combo_box_get_model (GTK_COMBO_BOX (selector));
	if (!gtk_tree_model_get_iter_first (model, &iter))
		return FALSE;

	do {
		BraseroDrive *iter_drive;

		gtk_tree_model_get (model, &iter,
				    DRIVE_COL, &iter_drive,
				    -1);

		if (drive == iter_drive) {
			if (iter_drive)
				g_object_unref (iter_drive);

			gtk_combo_box_set_active_iter (GTK_COMBO_BOX (selector), &iter);
			brasero_drive_selection_set_current_drive (selector, &iter);
			result = TRUE;
			break;
		}

		g_object_unref (iter_drive);
	} while (gtk_tree_model_iter_next (model, &iter));

	return result;
}
