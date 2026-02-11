st_theme_node_get_foreground_color (StThemeNode  *node,
                                    ClutterColor *color)
{
  g_return_if_fail (ST_IS_THEME_NODE (node));

  if (!node->foreground_computed)
    {
      int i;

      node->foreground_computed = TRUE;

      ensure_properties (node);

      for (i = node->n_properties - 1; i >= 0; i--)
        {
          CRDeclaration *decl = node->properties[i];

          if (strcmp (decl->property->stryng->str, "color") == 0)
            {
              GetFromTermResult result = get_color_from_term (node, decl->value, &node->foreground_color);
              if (result == VALUE_FOUND)
                goto out;
              else if (result == VALUE_INHERIT)
                break;
            }
        }

      if (node->parent_node)
        st_theme_node_get_foreground_color (node->parent_node, &node->foreground_color);
      else
        node->foreground_color = BLACK_COLOR;
    }

 out:
  *color = node->foreground_color;
}
