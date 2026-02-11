brasero_app_indicator_set_progress (BraseroAppIndicator *indicator,
				    gdouble fraction,
				    glong remaining)
{
	gint percent;
	gint remains;
	gchar *icon_name;

	percent = fraction * 100;
	indicator->priv->percent = percent;


	brasero_app_indicator_set_progress_menu_text (indicator, remaining);


	remains = percent % 5;
	if (remains > 3)
		percent += 5 - remains;
	else
		percent -= remains;

	if (indicator->priv->rounded_percent == percent
	||  percent < 0 || percent > 100)
		return;

	indicator->priv->rounded_percent = percent;

	icon_name = g_strdup_printf ("brasero-disc-%02i", percent);
	app_indicator_set_icon_full(indicator->priv->indicator,
			       icon_name, accessible_desc);
	g_free (icon_name);
}
