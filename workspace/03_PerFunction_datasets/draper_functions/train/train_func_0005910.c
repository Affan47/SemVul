ensure_vis_plugins_list (BaconVideoWidget *bvw)
{
  GHashTable *ht;
  GList *features;

  if (bvw->priv->vis_plugins_ht)
    return;

  features = get_visualization_features ();
  ht = g_hash_table_new (g_str_hash, g_str_equal);
  g_list_foreach (features, (GFunc) add_longname, ht);
  g_list_free (features);

  bvw->priv->vis_plugins_ht = ht;
}
