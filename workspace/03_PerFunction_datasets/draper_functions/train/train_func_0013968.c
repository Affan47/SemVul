clutter_text_node_finalize (ClutterPaintNode *node)
{
  ClutterTextNode *tnode = CLUTTER_TEXT_NODE (node);

  if (tnode->layout != NULL)
    g_object_unref (tnode->layout);

  CLUTTER_PAINT_NODE_CLASS (clutter_text_node_parent_class)->finalize (node);
}
