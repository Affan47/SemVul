gd_stack_get_child_property (GtkContainer *container,
                             GtkWidget    *child,
                             guint         property_id,
                             GValue       *value,
                             GParamSpec   *pspec)
{
  GdStack *stack = GD_STACK (container);
  GdStackChildInfo *info;
  GList *list;
  guint i;

  info = find_child_info_for_widget (stack, child);
  if (info == NULL)
    {
      GTK_CONTAINER_WARN_INVALID_CHILD_PROPERTY_ID (container, property_id, pspec);
      return;
    }

  switch (property_id)
    {
    case CHILD_PROP_NAME:
      g_value_set_string (value, info->name);
      break;

    case CHILD_PROP_TITLE:
      g_value_set_string (value, info->title);
      break;

    case CHILD_PROP_SYMBOLIC_ICON_NAME:
      g_value_set_string (value, info->symbolic_icon_name);
      break;

    case CHILD_PROP_POSITION:
      i = 0;
      for (list = stack->priv->children; list != NULL; list = g_list_next (list))
        {
          if (info == list->data)
            break;
          ++i;
        }
      g_value_set_int (value, i);
      break;

    default:
      GTK_CONTAINER_WARN_INVALID_CHILD_PROPERTY_ID (container, property_id, pspec);
      break;
    }
}
