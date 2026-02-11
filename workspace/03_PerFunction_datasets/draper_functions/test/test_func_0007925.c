exo_icon_view_drag_drop (GtkWidget      *widget,
                         GdkDragContext *context,
                         gint            x,
                         gint            y,
                         guint           drag_time)
{
  ExoIconView *icon_view;
  GtkTreePath *path;
  GdkDragAction suggested_action = 0;
  GdkAtom target = GDK_NONE;
  GtkTreeModel *model;
  gboolean drop_append_mode;

  icon_view = EXO_ICON_VIEW (widget);
  model = exo_icon_view_get_model (icon_view);

  remove_scroll_timeout (EXO_ICON_VIEW (widget));

  if (!icon_view->priv->dest_set)
    return FALSE;

  if (!check_model_dnd (model, GTK_TYPE_TREE_DRAG_DEST, "drag_drop"))
    return FALSE;

  if (!set_destination (icon_view, context, x, y, &suggested_action, &target))
    return FALSE;

  path = get_logical_destination (icon_view, &drop_append_mode);

  if (target != GDK_NONE && path != NULL)
    {


      set_status_pending (context, 0);
      set_dest_row (context, model, path,
                    icon_view->priv->empty_view_drop, drop_append_mode);
    }

  if (path)
    gtk_tree_path_free (path);


  exo_icon_view_set_drag_dest_item (icon_view, NULL, EXO_ICON_VIEW_DROP_LEFT);

  if (target != GDK_NONE)
    {
      gtk_drag_get_data (widget, context, target, drag_time);
      return TRUE;
    }
  else
    return FALSE;
}
