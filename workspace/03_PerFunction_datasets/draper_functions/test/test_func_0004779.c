garcon_menu_finalize (GObject *object)
{
  GarconMenu *menu = GARCON_MENU (object);


  garcon_menu_clear (menu);


  if (menu->priv->file != NULL)
    g_object_unref (menu->priv->file);


  g_object_unref (menu->priv->pool);


  g_object_unref (menu->priv->cache);

  (*G_OBJECT_CLASS (garcon_menu_parent_class)->finalize) (object);
}
