gtk_meta_expose(GtkWidget *widget, GdkEventExpose *event)
{
	if (event->count==0) {
		GtkMeta *meta = GTK_META(widget);

		if (!meta->playing) {
			meta->draw = meta->pixmap;
			playmeta();
			gdk_draw_pixmap(widget->window,meta->gc,meta->pixmap,0,0,0,0,-1,-1);
			meta->draw = widget->window;
		}
	}
	return FALSE;
}
