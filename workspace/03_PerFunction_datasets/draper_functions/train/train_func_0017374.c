st_theme_context_get_root_node (StThemeContext *context)
{
  if (context->root_node == NULL)
    context->root_node = st_theme_node_new (context, NULL, context->theme,
                                            G_TYPE_NONE, NULL, NULL, NULL, NULL);

  return context->root_node;
}
