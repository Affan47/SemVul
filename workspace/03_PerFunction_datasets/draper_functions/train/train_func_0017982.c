_save_assets (GString * str, GESProject * project)
{
  char *properties, *metas;
  GESAsset *asset;
  GList *assets, *tmp;

  assets = ges_project_list_assets (project, GES_TYPE_EXTRACTABLE);
  for (tmp = assets; tmp; tmp = tmp->next) {
    asset = GES_ASSET (tmp->data);
    properties = _serialize_properties (G_OBJECT (asset), NULL);
    metas = ges_meta_container_metas_to_string (GES_META_CONTAINER (asset));
    append_escaped (str,
        g_markup_printf_escaped
        ("      <asset id='%s' extractable-type-name='%s' properties='%s' metadatas='%s' />\n",
            ges_asset_get_id (asset),
            g_type_name (ges_asset_get_extractable_type (asset)), properties,
            metas));
    g_free (properties);
    g_free (metas);
  }
  g_list_free_full (assets, gst_object_unref);
}
