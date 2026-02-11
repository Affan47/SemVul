gtk_enhanced_scale_pos_trough ( GtkEnhancedScale *enhanced_scale,
        gint *x, gint *y, gint *w, gint *h )
{
	GtkWidget * widget;
	gint trough_border, slider_width;

	g_return_if_fail ( enhanced_scale != NULL );
	g_return_if_fail ( GTK_IS_ENHANCED_SCALE ( enhanced_scale ) );
	g_return_if_fail ( ( x != NULL ) && ( y != NULL ) && ( w != NULL ) && ( h != NULL ) );

	widget = GTK_WIDGET ( enhanced_scale );
	trough_border = gtk_enhanced_scale_get_trough_border( GTK_WIDGET( enhanced_scale ) );
	slider_width = gtk_enhanced_scale_get_slider_width( GTK_WIDGET( enhanced_scale ) );

	*w = widget->allocation.width - 2;
	*h = ( slider_width + trough_border * 2 );
	*x = 1;
	*y = ( widget->allocation.height - *h ) / 2;
}
