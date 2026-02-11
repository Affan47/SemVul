addressbook_window_dispose (GObject *obj)
{
  AddressBookWindow *self = ADDRESSBOOK_WINDOW (obj);

  if (self->priv->menu_item_view) {

    g_object_unref (self->priv->menu_item_view);
    self->priv->menu_item_view = NULL;
  }

  if (self->priv->menu_item_core) {

    g_object_unref (self->priv->menu_item_core);
    self->priv->menu_item_core = NULL;
  }

  G_OBJECT_CLASS (addressbook_window_parent_class)->dispose (obj);
}
