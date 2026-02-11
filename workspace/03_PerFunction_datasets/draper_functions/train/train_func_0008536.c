item_event_imageset_selector(GooCanvasItem *item, GdkEvent *event,
			     gpointer data)
{
  GSList *image_list;
  GooCanvasItem *rootitem_set;
  guint imageset_done;
  gdouble last_iy;

  if(display_in_progress)
    return TRUE;

  display_in_progress = TRUE;


  image_list = (GSList *)g_object_get_data (G_OBJECT (item), "imagelist");
  g_return_val_if_fail (image_list != NULL, FALSE);


  rootitem_set = (GooCanvasItem *)g_object_get_data (G_OBJECT (item),
						     "rootitem");
  g_return_val_if_fail (rootitem_set != NULL, FALSE);

  imageset_done = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (item),
						      "imageset_done"));


  if (current_root_set != NULL) {
    g_object_set (current_root_set,
		  "visibility", GOO_CANVAS_ITEM_INVISIBLE,
		  NULL);
  }

  if(!imageset_done)
    {

      ix = 0;
      iy = 0;

      g_slist_foreach (image_list, (GFunc) display_image, rootitem_set);
      g_object_set_data (G_OBJECT (item), "imageset_done", GINT_TO_POINTER (1));
    }


  last_iy = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (rootitem_set), "iy"));
  gdouble upper = MAX(last_iy,
		      (DRAWING_AREA_Y2 - DRAWING_AREA_Y1)
		      * gc_zoom_factor_get());

  goo_canvas_set_bounds  (GOO_CANVAS(canvas_image_selector),
			  0, 0,
			  (DRAWING_AREA_X2 - DRAWING_AREA_X1)
			  * gc_zoom_factor_get(),
			  upper);

  g_object_set(image_bg_item,
	       "height", upper,
	       NULL);

  g_object_set(image_adj,
  	       "upper", last_iy,
  	       NULL);
  gtk_adjustment_set_value(image_adj, 0);

  g_object_set(rootitem_set,
	       "visibility", GOO_CANVAS_ITEM_VISIBLE, NULL);

  current_root_set = rootitem_set;

  display_in_progress = FALSE;

  return FALSE;

}
