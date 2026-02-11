st_theme_node_transition_get_paint_box (StThemeNodeTransition *transition,
                                        const ClutterActorBox *allocation,
                                        ClutterActorBox       *paint_box)
{
  StThemeNodeTransitionPrivate *priv = transition->priv;
  ClutterActorBox old_node_box, new_node_box;

  st_theme_node_get_paint_box (priv->old_theme_node,
                               allocation,
                               &old_node_box);

  st_theme_node_get_paint_box (priv->new_theme_node,
                               allocation,
                               &new_node_box);

  paint_box->x1 = MIN (old_node_box.x1, new_node_box.x1);
  paint_box->y1 = MIN (old_node_box.y1, new_node_box.y1);
  paint_box->x2 = MAX (old_node_box.x2, new_node_box.x2);
  paint_box->y2 = MAX (old_node_box.y2, new_node_box.y2);
}
