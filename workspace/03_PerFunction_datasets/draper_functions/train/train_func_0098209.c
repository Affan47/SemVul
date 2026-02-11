piechart_calculation(GtkChart *chart)
{
GtkWidget *drawarea = chart->drawarea;
GtkAllocation allocation;
gint w, h;

	w = chart->graph_width;
	h = chart->graph_height;

	chart->rayon = MIN(w, h);

	gtk_widget_get_allocation(drawarea, &allocation);
	chart->ox    = allocation.width / 2;
	chart->oy    = chart->graph_y + (chart->rayon / 2) + 1;

}
