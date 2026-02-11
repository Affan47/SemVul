gtk_enhanced_scale_button_release( GtkWidget *widget, GdkEventButton *event )
{
	GtkEnhancedScale * enhanced_scale;

	g_return_val_if_fail ( widget != NULL, FALSE );
	g_return_val_if_fail ( GTK_IS_ENHANCED_SCALE ( widget ), FALSE );
	g_return_val_if_fail ( event != NULL, FALSE );

	enhanced_scale = GTK_ENHANCED_SCALE ( widget );

#ifdef DEBUG
	printf( "Button released" );
	if ( enhanced_scale->clicked_slider != -1 )
		printf( " - slider %d unselected", enhanced_scale->clicked_slider );
	printf( "\n" );
#endif

	enhanced_scale->x_click_point = 0;
	enhanced_scale->clicked_slider = -1;
	gtk_widget_queue_draw ( widget );

	return TRUE;
}
