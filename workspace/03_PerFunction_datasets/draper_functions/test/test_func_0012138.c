draw_car(car *thiscar)
{
  GooCanvasItem *car_group;
  GooCanvasItem *car_rect;

  g_object_set_data(G_OBJECT(allcars),"whatami",(gpointer)"allcars");

  car_group = goo_canvas_group_new(allcars,
				   NULL);
  goo_canvas_item_translate(car_group,
			    40.0 * thiscar->x - 10,
			    40.0 * thiscar->y - 10);

  car_rect = goo_canvas_rect_new(car_group,
				 0.0,
				 0.0,
				 (thiscar->orient?40.0*thiscar->size:40.0)-2,
				 (thiscar->orient?40.0:40.0*thiscar->size)-2,
				 "fill_color_rgba", thiscar->color,
				 "stroke-color", "white",
				 "line-width", 1.0,
				 NULL);

  g_signal_connect(car_group,"button_press_event",
		   GTK_SIGNAL_FUNC(on_button_press), (gpointer)thiscar);
  g_signal_connect (car_group, "button_release_event",
		    (GCallback) on_button_release, (gpointer)thiscar);
  g_signal_connect (car_group, "motion_notify_event",
		    (GCallback) on_motion_notify, (gpointer)thiscar);

  g_object_set_data(G_OBJECT(car_group), "car", (gpointer)thiscar);
  g_object_set_data(G_OBJECT(car_group), "whatami", (gpointer)"car_group");
  g_object_set_data(G_OBJECT(car_rect), "whatami", (gpointer)"car_rect");
}
