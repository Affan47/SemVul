railroad_create_item(GooCanvasItem *boardRootItem)
{
  int xOffset = 0, yOffset = 0;
  int i, r, l = 1;
  GdkPixbuf * pixmap = NULL;
  GooCanvasItem *item;


  answerRootItem = goo_canvas_group_new (boardRootItem, NULL);


  allwagonsRootItem = goo_canvas_group_new (boardRootItem, NULL);

  for (i=0; i<ENGINES+WAGONS; i++) {
    if (i<ENGINES)
      pixmap = g_list_nth_data(listPixmapEngines, i);
    else
      pixmap = g_list_nth_data(listPixmapWagons, i-ENGINES);

    if ( (xOffset + gdk_pixbuf_get_width(pixmap)) >= BOARDWIDTH) {
      xOffset = 0;
      l++;
    }
    yOffset = line[l] - gdk_pixbuf_get_height(pixmap);

    item = goo_canvas_image_new (allwagonsRootItem,
				 pixmap,
				 xOffset,
				 yOffset,
				 NULL);
    xOffset += gdk_pixbuf_get_width(pixmap);

    g_signal_connect(item,
		     "button_press_event", (GCallback) item_event,
		     GINT_TO_POINTER(i));

  }

  g_object_set (allwagonsRootItem, "visibility", GOO_CANVAS_ITEM_INVISIBLE, NULL);


  modelRootItem = goo_canvas_group_new (boardRootItem, NULL);

  yOffset = line[0];
  xOffset = 0;
  model_size = gcomprisBoard->level +1;

  for (i=0; i<model_size-1; i++) {
    r = g_random_int_range( 0, WAGONS);
    g_assert( r >=0 && r < WAGONS);

    int_model_list = g_list_append(int_model_list, GINT_TO_POINTER(r+ENGINES));
    pixmap = g_list_nth_data(listPixmapWagons, r);
    g_assert(i >= 0 && i<MODEL_MAX_SIZE);
    item_model[i] = goo_canvas_image_new (modelRootItem,
					  pixmap,
					  xOffset,
					  yOffset - gdk_pixbuf_get_height(pixmap),
					  NULL);
    g_signal_connect(item_model[i],
		     "button_press_event", (GCallback) stop_animation,
		     NULL);
    xOffset  += gdk_pixbuf_get_width(pixmap);
  }


  r = g_random_int_range( 0, ENGINES);
  g_assert( r >=0 && r < ENGINES);

  int_model_list = g_list_append(int_model_list, GINT_TO_POINTER(r));
  pixmap = g_list_nth_data(listPixmapEngines, r);
  item_model[model_size-1] =goo_canvas_image_new (modelRootItem,
						  pixmap,
						  xOffset,
						  yOffset  - gdk_pixbuf_get_height(pixmap),
						  NULL);

  g_signal_connect(item_model[model_size-1],
		   "button_press_event", (GCallback) stop_animation,
		   NULL);
  animate_model();

  return NULL;
}
