goo_canvas_table_add_child     (GooCanvasItem  *item,
				GooCanvasItem  *child,
				gint            position)
{
  GooCanvasItemSimple *simple = (GooCanvasItemSimple*) item;
  GooCanvasTable *table = (GooCanvasTable*) item;

  if (!simple->model)
    goo_canvas_table_add_child_internal (table->table_data, position);


  goo_canvas_table_parent_iface->add_child (item, child, position);
}
