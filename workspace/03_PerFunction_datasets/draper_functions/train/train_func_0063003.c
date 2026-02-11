gtk_plot_surface_build_polygons(GtkPlotSurface *surface)
{
  GList *list;

  clear_polygons(surface);
  list = surface->dt->triangles;
  while(list){
    GtkPlotPolygon *polygon;
    GtkPlotDTtriangle *triangle = (GtkPlotDTtriangle *)list->data;

    polygon = g_new0(GtkPlotPolygon, 1);
    polygon->t = triangle;
    polygon->n = 3;
    polygon->cut_level = FALSE;
    polygon->xyz[0].x = triangle->na->x;
    polygon->xyz[0].y = triangle->na->y;
    polygon->xyz[0].z = triangle->na->z;
    polygon->xyz[1].x = triangle->nb->x;
    polygon->xyz[1].y = triangle->nb->y;
    polygon->xyz[1].z = triangle->nb->z;
    polygon->xyz[2].x = triangle->nc->x;
    polygon->xyz[2].y = triangle->nc->y;
    polygon->xyz[2].z = triangle->nc->z;
    surface->polygons = g_list_append(surface->polygons, polygon);

    list = list->next;
  };
}
