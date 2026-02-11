p_tabw_scroll_event_cb ( GtkWidget *widget
                    , GdkEventScroll *sevent
                    , GapStbTabWidgets *tabw
                    )
{
  gint32  value;


  if(tabw == NULL) { return FALSE;}

  value = (gint32)GTK_ADJUSTMENT(tabw->rowpage_spinbutton_adj)->value;

  if((sevent->direction == GDK_SCROLL_UP)
  || (sevent->direction == GDK_SCROLL_RIGHT))
  {
    value--;
  }
  else
  {
    value++;
  }


  gtk_adjustment_set_value(GTK_ADJUSTMENT(tabw->rowpage_spinbutton_adj), (gdouble)value);

  return FALSE;
}
