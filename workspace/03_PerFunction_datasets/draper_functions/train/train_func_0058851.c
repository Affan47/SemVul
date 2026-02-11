show_frame_rect	( gboolean show )
{
	frame_rect_show = show;
	if( frame_rect != NULL )
	{
		if ( show )
		{
			gtk_widget_show( GTK_WIDGET(frame_rect) );
		}
		else
		{
			gtk_widget_hide( GTK_WIDGET(frame_rect) );
		}
	}
}
