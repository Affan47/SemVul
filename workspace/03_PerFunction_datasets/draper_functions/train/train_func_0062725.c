ui_std_icon (GtkIconFactory *ifactory, const char *name,
				const char *file)
{
  GtkStockItem stock;
  if (!gtk_stock_lookup (name, &stock))
  {
    GtkIconSet *iset = gtk_icon_set_new ();
    gtk_icon_set_add_source (iset, make_icon_source (file, -1, -1));
    gtk_icon_factory_add (ifactory, name, iset);
    return iset;
  }
  return NULL;
}
