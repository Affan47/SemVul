select_item_at_index (ClutterActor *scroll,
                      int           index_)
{
  ClutterPoint point;
  ClutterActor *menu, *item;
  gpointer old_selected;

  menu = clutter_actor_get_first_child (scroll);

  old_selected = g_object_get_data (G_OBJECT (scroll), "selected-item");
  if (old_selected != NULL)
    {
      item = clutter_actor_get_child_at_index (menu, GPOINTER_TO_INT (old_selected));
      clutter_text_set_color (CLUTTER_TEXT (item), CLUTTER_COLOR_White);
    }


  if (index_ < 0)
    index_ = clutter_actor_get_n_children (menu) - 1;
  else if (index_ >= clutter_actor_get_n_children (menu))
    index_ = 0;

  item = clutter_actor_get_child_at_index (menu, index_);
  clutter_actor_get_position (item, &point.x, &point.y);


  clutter_actor_save_easing_state (scroll);
  clutter_scroll_actor_scroll_to_point (CLUTTER_SCROLL_ACTOR (scroll), &point);
  clutter_actor_restore_easing_state (scroll);

  clutter_text_set_color (CLUTTER_TEXT (item), CLUTTER_COLOR_LightSkyBlue);


  g_object_set_data (G_OBJECT (scroll), "selected-item",
                     GINT_TO_POINTER (index_));
}
