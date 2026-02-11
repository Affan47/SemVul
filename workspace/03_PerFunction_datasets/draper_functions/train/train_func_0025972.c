glade_cell_renderer_icon_activate (GtkCellRenderer * cell,
                                   GdkEvent * event,
                                   GtkWidget * widget,
                                   const gchar * path,
                                   const GdkRectangle * background_area,
                                   const GdkRectangle * cell_area,
                                   GtkCellRendererState flags)
{
  GladeCellRendererIcon *cellicon;

  cellicon = GLADE_CELL_RENDERER_ICON (cell);
  if (cellicon->priv->activatable)
    {
      g_signal_emit (cell, icon_cell_signals[ACTIVATE], 0, path);
      return TRUE;
    }

  return FALSE;
}
