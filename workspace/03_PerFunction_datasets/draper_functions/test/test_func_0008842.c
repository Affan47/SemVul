clutter_layout_manager_get_preferred_height (ClutterLayoutManager *manager,
                                             ClutterContainer     *container,
                                             gfloat                for_width,
                                             gfloat               *min_height_p,
                                             gfloat               *nat_height_p)
{
  ClutterLayoutManagerClass *klass;

  g_return_if_fail (CLUTTER_IS_LAYOUT_MANAGER (manager));
  g_return_if_fail (CLUTTER_IS_CONTAINER (container));

  klass = CLUTTER_LAYOUT_MANAGER_GET_CLASS (manager);
  klass->get_preferred_height (manager, container, for_width,
                               min_height_p,
                               nat_height_p);
}
