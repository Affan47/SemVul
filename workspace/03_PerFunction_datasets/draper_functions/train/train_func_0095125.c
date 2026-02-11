ClearPoint(GtkWidget * widget, int x, int y, int update)
{

	gn_bmp_point_clear(&bitmap, x, y);


	gdk_draw_pixmap(drawingPixmap, widget->style->fg_gc[GTK_WIDGET_STATE(widget)],
			greenPointPixmap, 0, 0, x * (POINTSIZE + 1), y * (POINTSIZE + 1), -1, -1);

	if (update) {
		GdkRectangle updateRect;


		updateRect.width = POINTSIZE + 2;
		updateRect.height = POINTSIZE + 2;
		updateRect.x = x * (POINTSIZE + 1);
		updateRect.y = y * (POINTSIZE + 1);


		gtk_widget_draw(drawingArea, &updateRect);
	}


	if (previewAvailable)
		ClearPreviewPoint(widget, x, y, update);
}
