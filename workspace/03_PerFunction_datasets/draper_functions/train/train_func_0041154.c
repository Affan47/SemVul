goo_canvas_remove (GtkContainer *container,
		   GtkWidget    *widget)
{
  GooCanvas *canvas;
  GList *tmp_list;
  GooCanvasWidget *witem;
  GooCanvasItem *parent;
  gint child_num;

  g_return_if_fail (GOO_IS_CANVAS (container));

  canvas = GOO_CANVAS (container);

  tmp_list = canvas->widget_items;
  while (tmp_list)
    {
      witem = tmp_list->data;
      tmp_list = tmp_list->next;

      if (witem->widget == widget)
	{
	  parent = goo_canvas_item_get_parent ((GooCanvasItem*) witem);
	  child_num = goo_canvas_item_find_child (parent,
						  (GooCanvasItem*) witem);
	  goo_canvas_item_remove_child (parent, child_num);

	  break;
	}
    }
}
