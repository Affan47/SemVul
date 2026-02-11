p_rowpage_spinbutton_cb( GtkEditable     *editable
                       , GapStbTabWidgets *tabw)
{
  gint32 rowpage;

  if(tabw == NULL) { return; }

  rowpage = (gint32)GTK_ADJUSTMENT(tabw->rowpage_spinbutton_adj)->value;
  if(rowpage != tabw->rowpage)
  {
    p_tabw_set_rowpage_and_refresh(tabw, rowpage);
  }
  if(rowpage != (gint32)GTK_ADJUSTMENT(tabw->rowpage_vscale_adj)->value)
  {
    gtk_adjustment_set_value(GTK_ADJUSTMENT(tabw->rowpage_vscale_adj), (gdouble)rowpage);
  }

}
