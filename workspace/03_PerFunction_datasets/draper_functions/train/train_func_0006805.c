gtk_cmclist_set_row_height (GtkCMCList *clist,
			  guint     height)
{
  GtkStyle *style;
  GtkWidget *widget;

  cm_return_if_fail (GTK_IS_CMCLIST (clist));

  widget = GTK_WIDGET (clist);

  style = gtk_widget_get_style (widget);

  if (height > 0)
    {
      clist->row_height = height;
      GTK_CMCLIST_SET_FLAG (clist, CMCLIST_ROW_HEIGHT_SET);
    }
  else
    {
      GTK_CMCLIST_UNSET_FLAG (clist, CMCLIST_ROW_HEIGHT_SET);
      clist->row_height = 0;
    }

  if (style->font_desc)
    {
      PangoContext *context = gtk_widget_get_pango_context (widget);
      PangoFontMetrics *metrics;

      metrics = pango_context_get_metrics (context,
					   style->font_desc,
					   pango_context_get_language (context));

      if (!GTK_CMCLIST_ROW_HEIGHT_SET(clist))
	{
	  clist->row_height = (pango_font_metrics_get_ascent (metrics) +
			       pango_font_metrics_get_descent (metrics));
	  clist->row_height = PANGO_PIXELS (clist->row_height) + 1;
	}

      pango_font_metrics_unref (metrics);
    }

  CLIST_REFRESH (clist);
}
