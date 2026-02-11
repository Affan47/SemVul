gtkstock_create_close( GtkWidget *widget, GtkAccelGroup *accel,
		       GCallback destroy, gboolean esconly )
{
  gtkstock_button btn = {
    GTK_STOCK_CLOSE, NULL, NULL, (destroy ? destroy : DEFAULT_DESTROY),
    (esconly ? GDK_KEY_VoidSymbol : 0), 0, 0, 0
  };
  return gtkstock_create_buttons( widget, accel, &btn, 1 );
}
