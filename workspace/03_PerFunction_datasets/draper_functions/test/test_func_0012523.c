gd_stack_set_transition_position (GdStack *stack,
                                  gdouble pos)
{
  GdStackPrivate *priv = stack->priv;
  GtkAllocation allocation;
  gboolean done;

  priv->transition_pos = pos;
  gtk_widget_queue_draw (GTK_WIDGET (stack));

  if (priv->transition_type == GD_STACK_TRANSITION_TYPE_SLIDE_LEFT ||
      priv->transition_type == GD_STACK_TRANSITION_TYPE_SLIDE_RIGHT)
    {
      gtk_widget_get_allocation (GTK_WIDGET (stack), &allocation);
      gdk_window_move (priv->bin_window,
                       get_bin_window_x (stack, &allocation), 0);
    }

  done = pos >= 1.0;

  if (done || priv->last_visible_surface != NULL)
    {
      if (priv->last_visible_child)
        {
          gtk_widget_set_child_visible (priv->last_visible_child->widget, FALSE);
          priv->last_visible_child = NULL;
        }
    }

  if (done)
    {
      if (priv->last_visible_surface != NULL)
        {
          cairo_surface_destroy (priv->last_visible_surface);
          priv->last_visible_surface = NULL;
        }

      gtk_widget_queue_resize (GTK_WIDGET (stack));
    }

  return done;
}
