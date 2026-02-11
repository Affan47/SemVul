gtr_tab_label_constructed (GObject *object)
{
  GtrTabLabel *tab_label = GTR_TAB_LABEL (object);

  if (!tab_label->priv->tab)
    {
      g_critical ("The tab label was not properly constructed");
      return;
    }

  sync_name (tab_label->priv->tab, NULL, tab_label);


  g_signal_connect_object (tab_label->priv->tab,
                           "notify::name",
                           G_CALLBACK (sync_name),
                           tab_label,
                           0);


}
