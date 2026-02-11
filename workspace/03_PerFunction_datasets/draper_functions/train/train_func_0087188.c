create_demo_item (GooCanvasItem *table,
		  gint           demo_item_type,
		  gint           row,
		  gint           column,
		  gint           rows,
		  gint           columns,
		  gchar         *text,
		  gdouble	 width,
		  gdouble        xalign,
		  gdouble	 yalign,
		  PangoAlignment text_alignment)
{
  GooCanvasItem *item = NULL;
  GtkWidget *widget;
  GValue value = { 0 };
  guint new_row;

  switch (demo_item_type)
    {
    case DEMO_RECT_ITEM:
      item = goo_canvas_rect_new (table, 0, 0, 38, 19,
				  "fill-color", "red",
				  NULL);
      break;
    case DEMO_TEXT_ITEM:
    case DEMO_TEXT_ITEM_2:
    case DEMO_TEXT_ITEM_3:
      item = goo_canvas_text_new (table, text, 0, 0, width, GOO_CANVAS_ANCHOR_NW,
				  "alignment",  text_alignment,
				  NULL);
      break;
    case DEMO_WIDGET_ITEM:
      widget = gtk_button_new_with_label (text);
      item = goo_canvas_widget_new (table, widget, 0, 0, -1, -1, NULL);
      break;
    }

  g_value_init (&value, G_TYPE_UINT);
  g_value_set_uint (&value, row);
  goo_canvas_item_set_child_property (table, item, "row", &value);
  g_value_set_uint (&value, column);
  goo_canvas_item_set_child_property (table, item, "column", &value);
  g_value_set_uint (&value, rows);
  goo_canvas_item_set_child_property (table, item, "rows", &value);
  g_value_set_uint (&value, columns);
  goo_canvas_item_set_child_property (table, item, "columns", &value);

  goo_canvas_item_set_child_properties (table, item,
					"x-expand", TRUE,
					"y-expand", TRUE,
					"x-align", xalign,
					"y-align", yalign,
					NULL);


  goo_canvas_item_get_child_property (table, item, "row", &value);
  new_row = g_value_get_uint (&value);
  if (new_row != row)
    g_warning ("Got bad row setting: %i should be: %i\n", new_row, row);


#if 0
  goo_canvas_item_set_child_properties (table, item,
					"x-fill", TRUE,
					"y-fill", TRUE,
					NULL);
#endif

  g_object_set_data (G_OBJECT (item), "id", text);
  g_signal_connect (item, "button_press_event",
		    G_CALLBACK (on_button_press), NULL);
}
