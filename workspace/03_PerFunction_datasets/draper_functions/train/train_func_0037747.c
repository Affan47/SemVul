Draw_Partition()
{
	UNUSED = X_END - X_START - BORDER * 2 - USED ;
	if ( UNUSED < 0 )
		UNUSED = 0 ;

	if ( drawingarea .get_window() )
	{

		gc_pixmap ->set_foreground( color_background );
		pixmap ->draw_rectangle( gc_pixmap, true, 0, 0, 536, 50 );


		gc_pixmap ->set_foreground( color_arrow_rectangle );
		pixmap ->draw_rectangle( gc_pixmap, true, 0, 0, 10, 50 );
		pixmap ->draw_rectangle( gc_pixmap, true, 526, 0, 10, 50 );


		gc_pixmap ->set_foreground( color_partition );
		pixmap ->draw_rectangle( gc_pixmap, true, X_START, 0, X_END - X_START, 50 );


		gc_pixmap ->set_foreground( color_used );
		pixmap ->draw_rectangle( gc_pixmap, true, X_START +BORDER, BORDER, USED, 34 );


		gc_pixmap ->set_foreground( color_unused );
		pixmap ->draw_rectangle( gc_pixmap, true, X_START +BORDER +USED, BORDER, UNUSED, 34 );


		if ( ! fixed_start )
			Draw_Resize_Grip( ARROW_LEFT ) ;

		Draw_Resize_Grip( ARROW_RIGHT ) ;


		drawingarea .get_window() ->draw_drawable( gc_drawingarea, pixmap, 0, 0, 0, 0 ) ;
	}
}
