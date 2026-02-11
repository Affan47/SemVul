egg_list_box_real_get_preferred_width (GtkWidget* widget, gint* minimum_width_out, gint* natural_width_out)
{
  EggListBox *list_box = EGG_LIST_BOX (widget);
  EggListBoxPrivate *priv = list_box->priv;
  gint minimum_width;
  gint natural_width;
  GtkStyleContext *context;
  gint focus_width;
  gint focus_pad;
  GSequenceIter *iter;
  EggListBoxChildInfo *child_info;
  GtkWidget *child;
  gint child_min;
  gint child_nat;

  context = gtk_widget_get_style_context (GTK_WIDGET (list_box));
  gtk_style_context_get_style (context, "focus-line-width", &focus_width, "focus-padding", &focus_pad, NULL);

  minimum_width = 0;
  natural_width = 0;

  for (iter = g_sequence_get_begin_iter (priv->children);
       !g_sequence_iter_is_end (iter);
       iter = g_sequence_iter_next (iter))
    {
      child_info = g_sequence_get (iter);
      child = child_info->widget;
      if (!child_is_visible (child))
	continue;

      gtk_widget_get_preferred_width (child, &child_min, &child_nat);
      minimum_width = MAX (minimum_width, child_min + 2 * (focus_width + focus_pad));
      natural_width = MAX (natural_width, child_nat + 2 * (focus_width + focus_pad));

      if (child_info->separator != NULL)
	{
	  gtk_widget_get_preferred_width (child_info->separator, &child_min, &child_nat);
	  minimum_width = MAX (minimum_width, child_min);
	  natural_width = MAX (natural_width, child_nat);
	}
    }

  if (minimum_width_out)
    *minimum_width_out = minimum_width;
  if (natural_width_out)
    *natural_width_out = natural_width;
}
