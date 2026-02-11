st_box_layout_get_vertical (StBoxLayout *box)
{
  ClutterLayoutManager *layout;
  ClutterOrientation orientation;

  g_return_val_if_fail (ST_IS_BOX_LAYOUT (box), FALSE);

  layout = clutter_actor_get_layout_manager (CLUTTER_ACTOR (box));
  orientation = clutter_box_layout_get_orientation (CLUTTER_BOX_LAYOUT (layout));
  return orientation == CLUTTER_ORIENTATION_VERTICAL;
}
