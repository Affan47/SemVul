cb_engineering_toggle (GtkWidget *w, GOFormatSel *gfs)
{
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (w)))
		gfs->format.details.exponent_step = 3;
	else
		gfs->format.details.exponent_step = 1;

	draw_format_preview (gfs, TRUE);
}
