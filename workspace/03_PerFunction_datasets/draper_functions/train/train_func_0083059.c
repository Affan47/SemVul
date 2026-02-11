clutter_grid_request_update_child_attach (ClutterGridRequest *request,
                                          ClutterActor       *actor)
{
  ClutterGridLayoutPrivate *priv = request->grid->priv;
  ClutterGridChild *grid_child;

  grid_child = GET_GRID_CHILD (request->grid, actor);

  if (CHILD_LEFT (grid_child) == -1 || CHILD_TOP (grid_child) == -1)
    {
      ClutterGridPosition side;
      ClutterActor *sibling;

      if (priv->orientation == CLUTTER_ORIENTATION_HORIZONTAL)
        {
          ClutterTextDirection td;
          gboolean rtl;
          ClutterActor *container = CLUTTER_ACTOR (priv->container);

          td = clutter_actor_get_text_direction (container);
          rtl = (td == CLUTTER_TEXT_DIRECTION_RTL) ? TRUE : FALSE;
          side = rtl ? CLUTTER_GRID_POSITION_LEFT : CLUTTER_GRID_POSITION_RIGHT;
        }
      else
        {


          side = CLUTTER_GRID_POSITION_BOTTOM;
        }

      sibling = clutter_actor_get_previous_sibling (actor);
      if (sibling)
        clutter_grid_layout_insert_next_to (request->grid, sibling, side);
      grid_attach_next_to (request->grid, actor, sibling, side,
                           CHILD_WIDTH (grid_child),
                           CHILD_HEIGHT (grid_child));
    }
}
