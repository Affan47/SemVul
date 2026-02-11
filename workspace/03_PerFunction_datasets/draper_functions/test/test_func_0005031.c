glade_design_layout_get_preferred_width (GtkWidget *widget,
                                         gint *minimum, gint *natural)
{
  GtkWidget *child;
  GladeWidget *gchild;
  gint child_width = 0;
  guint border_width = 0;

  *minimum = 0;

  child = gtk_bin_get_child (GTK_BIN (widget));

  if (child && gtk_widget_get_visible (child))
    {
      GtkRequisition req;

      gchild = glade_widget_get_from_gobject (child);
      g_assert (gchild);

      gtk_widget_get_preferred_size (child, &req, NULL);

      g_object_get (gchild, "toplevel-width", &child_width, NULL);

      child_width = MAX (child_width, req.width);

      *minimum = MAX (*minimum, 2*PADDING + 2*OUTLINE_WIDTH + child_width);
    }

  border_width = gtk_container_get_border_width (GTK_CONTAINER (widget));
  *minimum += border_width * 2;
  *natural = *minimum;
}
