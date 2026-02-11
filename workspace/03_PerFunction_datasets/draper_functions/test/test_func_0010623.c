wcs_EW_cb(int dir, GtkWidget *wid, gpointer dialog)
{
	GtkWidget *button;
	char *text = NULL, buf[256];
	double d, ra = INV_DBL, step = INV_DBL, dec = INV_DBL, cosdec;
	int btnstate;

	if (gtk_object_get_data(GTK_OBJECT(dialog), "im_window") == NULL) {
		return;
	}
	button = gtk_object_get_data(GTK_OBJECT(dialog), "wcs_step_button");
	btnstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));

	text = named_entry_text(dialog, "wcs_ra_entry");
	if (!dms_to_degrees(text, &d))
		ra = d * 15.;
	g_free(text);
	text = named_entry_text(dialog, "wcs_dec_entry");
	if (!dms_to_degrees(text, &d))
		dec = d;
	g_free(text);
	text = named_entry_text(dialog, "wcs_h_scale_entry");
	if (!dms_to_degrees(text, &d))
		step = d * (double)dir * ( 1 + 9.0 * (btnstate > 0) ) / 3600.;
	g_free(text);

	if ( (ra != INV_DBL) && (step != INV_DBL) )
	{
		cosdec = cos(degrad(dec));
		if (cosdec < 1.85185185183088e-05)
			cosdec = 1.85185185183088e-05;
		ra += step / cosdec;
		if ( ra < 0 )
			ra += 360.;
		if ( ra >= 360 )
			ra -= 360.;
		degrees_to_dms_pr(buf, ra / 15. , 2);
		named_entry_set(dialog, "wcs_ra_entry", buf);
		wcsentry_cb(NULL, dialog);
	}
}
