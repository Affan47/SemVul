on_motion_event (GtkWidget      *widget,
		 GdkEventMotion *event,
		 gpointer user_data)
{
  GdMainView *self = user_data;
  GtkTreePath *path;

  if (self->priv->track_motion)
    {
      if (!self->priv->rubberband_select &&
	  (event->x - self->priv->button_down_x) * (event->x - self->priv->button_down_x) +
	  (event->y - self->priv->button_down_y) * (event->y - self->priv->button_down_y)  >
	  MAIN_VIEW_RUBBERBAND_SELECT_TRIGGER_LENGTH * MAIN_VIEW_RUBBERBAND_SELECT_TRIGGER_LENGTH)
	{
	  self->priv->rubberband_select = TRUE;
	  if (self->priv->button_press_item_path)
	    {
	      self->priv->rubberband_select_first_path =
		gtk_tree_path_new_from_string (self->priv->button_press_item_path);
	    }
	}

      if (self->priv->rubberband_select)
	{
	  path = gd_main_view_generic_get_path_at_pos (get_generic (self), event->x, event->y);
	  if (path != NULL)
	    {
	      if (self->priv->rubberband_select_first_path == NULL)
		self->priv->rubberband_select_first_path = gtk_tree_path_copy (path);

	      if (self->priv->rubberband_select_last_path == NULL ||
		  gtk_tree_path_compare (self->priv->rubberband_select_last_path, path) != 0)
		{
		  if (self->priv->rubberband_select_last_path)
		    gtk_tree_path_free (self->priv->rubberband_select_last_path);
		  self->priv->rubberband_select_last_path = path;

		  gd_main_view_generic_set_rubberband_range (get_generic (self),
							     self->priv->rubberband_select_first_path,
							     self->priv->rubberband_select_last_path);
		}
	      else
		gtk_tree_path_free (path);
	    }
	}
    }
  return FALSE;
}
