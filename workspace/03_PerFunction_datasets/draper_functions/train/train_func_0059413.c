cb_si_unit_toggle (GtkWidget *w, GOFormatSel *gfs)
{
	g_free (gfs->format.details.appended_SI_unit);
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (w))) {
		GtkComboBox *c = GTK_COMBO_BOX (gfs->format.widget[F_SI_UNIT_COMBO]);
		GtkTreeIter iter;
		GtkTreeModel *store = gtk_combo_box_get_model (c);
		if (gtk_combo_box_get_active_iter (c, &iter)) {
			gtk_tree_model_get (store, &iter, 1, &gfs->format.details.appended_SI_unit,
					    2, &gfs->format.details.scale, -1);
			if (gfs->format.details.scale == 3) {
				char *text = gfs->format.details.appended_SI_unit;
				gfs->format.details.appended_SI_unit = g_strdup (text + 1);
				g_free (text);
			}
		} else
			gfs->format.details.appended_SI_unit = NULL;
	} else {
		guint i;
		gfs->format.details.appended_SI_unit = g_strdup (gfs->format.default_si_unit);
		gfs->format.details.scale = 1;
		if (gfs->format.details.appended_SI_unit != NULL)
			for (i=0; i < G_N_ELEMENTS (si_units); i++)
				if (0 == strcmp (si_units[i].unit, gfs->format.details.appended_SI_unit)) {
					gfs->format.details.scale = si_units[i].scale;
					break;
				}
	}

	draw_format_preview (gfs, TRUE);
}
