_gtk_source_style_scheme_apply (GtkSourceStyleScheme *scheme,
				GtkWidget            *widget)
{
	GtkSourceStyle *style, *style2;
	GtkStyleContext *context;

	g_return_if_fail (GTK_SOURCE_IS_STYLE_SCHEME (scheme));
	g_return_if_fail (GTK_IS_WIDGET (widget));


	context = gtk_widget_get_style_context (GTK_WIDGET (widget));
	gtk_style_context_add_provider (context,
	                                GTK_STYLE_PROVIDER (scheme->priv->css),
	                                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	gtk_style_context_invalidate (context);

	style = gtk_source_style_scheme_get_style (scheme, STYLE_LINE_NUMBERS);
	set_line_numbers_style (widget, style);

	style = gtk_source_style_scheme_get_style (scheme, STYLE_CURSOR);
	style2 = gtk_source_style_scheme_get_style (scheme, STYLE_SECONDARY_CURSOR);
	update_cursor_colors (widget, style, style2);
}
