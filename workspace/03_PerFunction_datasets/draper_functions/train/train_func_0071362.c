delete_objects_line(GtkWidget *widget)
{
	GabeditContoursPlot *contoursplot = NULL;
	if(!widget) return;
	if(!GTK_IS_WIDGET(widget)) return;
	contoursplot = GABEDIT_ContoursPLOT(widget);
	contoursplot->nObjectsLine = 0;
	if(contoursplot->objectsLine) g_free(contoursplot->objectsLine);
	contoursplot->objectsLine = NULL;
	gtk_widget_queue_draw(GTK_WIDGET(contoursplot));
}
