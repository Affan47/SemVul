ges_base_xml_formatter_add_layer (GESBaseXmlFormatter * self,
    GType extractable_type, guint priority, GstStructure * properties,
    const gchar * metadatas, GError ** error)
{
  LayerEntry *entry;
  GESAsset *asset;
  GESLayer *layer;
  gboolean auto_transition = FALSE;
  GESBaseXmlFormatterPrivate *priv = _GET_PRIV (self);

  if (priv->check_only)
    return;

  if (extractable_type == G_TYPE_NONE)
    layer = ges_layer_new ();
  else {
    asset = ges_asset_request (extractable_type, NULL, error);
    if (asset == NULL) {
      if (error && *error == NULL) {
        g_set_error (error, G_MARKUP_ERROR,
            G_MARKUP_ERROR_INVALID_CONTENT,
            "Layer type %s could not be created'",
            g_type_name (extractable_type));
        return;
      }
    }
    layer = GES_LAYER (ges_asset_extract (asset, error));
  }

  ges_layer_set_priority (layer, priority);
  ges_timeline_add_layer (GES_FORMATTER (self)->timeline, layer);
  if (properties) {
    if (gst_structure_get_boolean (properties, "auto-transition",
            &auto_transition))
      gst_structure_remove_field (properties, "auto-transition");

    gst_structure_foreach (properties,
        (GstStructureForeachFunc) set_property_foreach, layer);
  }

  if (metadatas)
    ges_meta_container_add_metas_from_string (GES_META_CONTAINER (layer),
        metadatas);

  entry = g_slice_new0 (LayerEntry);
  entry->layer = gst_object_ref (layer);
  entry->auto_trans = auto_transition;

  g_hash_table_insert (priv->layers, GINT_TO_POINTER (priority), entry);
}
