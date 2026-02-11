_clutter_paint_node_paint (ClutterPaintNode *node)
{
  ClutterPaintNodeClass *klass = CLUTTER_PAINT_NODE_GET_CLASS (node);
  ClutterPaintNode *iter;
  gboolean res;

  res = klass->pre_draw (node);

  if (res)
    {
      klass->draw (node);
    }

  for (iter = node->first_child;
       iter != NULL;
       iter = iter->next_sibling)
    {
      _clutter_paint_node_paint (iter);
    }

  if (res)
    {
      klass->post_draw (node);
    }
}
