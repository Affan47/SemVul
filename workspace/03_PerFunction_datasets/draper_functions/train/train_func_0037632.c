on_focus_out (GooCanvasItem *item,
	      GooCanvasItem *target,
	      GdkEventFocus *event,
	      gpointer data)
{
  GooCanvasItemModel *model = goo_canvas_item_get_model (item);
  gchar *id = g_object_get_data (G_OBJECT (model), "id");

  g_print ("%s received focus-out event\n", id ? id : "unknown");


  g_object_set (model, "stroke-pattern", NULL, NULL);

  return FALSE;
}
