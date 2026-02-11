abiDestroyWidget(GtkWidget * me)
{
  if(me && GTK_IS_WIDGET(me))
    gtk_widget_destroy(me);
}
