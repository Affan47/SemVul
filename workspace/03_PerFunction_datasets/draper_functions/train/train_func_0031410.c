load_pitivi_file_from_uri (GESFormatter * self,
    GESTimeline * timeline, const gchar * uri, GError ** error)
{
  xmlDocPtr doc;
  GESLayer *layer;
  GESPitiviFormatterPrivate *priv = GES_PITIVI_FORMATTER (self)->priv;

  gboolean ret = TRUE;
  gint *prio = malloc (sizeof (gint));

  *prio = 0;
  layer = ges_layer_new ();
  g_object_set (layer, "auto-transition", TRUE, NULL);

  g_hash_table_insert (priv->layers_table, prio, layer);
  g_object_set (layer, "priority", (gint32) 0, NULL);

  if (!ges_timeline_add_layer (timeline, layer)) {
    GST_ERROR ("Couldn't add layer");
    return FALSE;
  }

  if (!(doc = xmlParseFile (uri))) {
    GST_ERROR ("The xptv file for uri %s was badly formed or did not exist",
        uri);
    return FALSE;
  }

  priv->xpathCtx = xmlXPathNewContext (doc);

  if (self->project)
    parse_metadatas (self);

  if (!create_tracks (self)) {
    GST_ERROR ("Couldn't create tracks");
    return FALSE;
  }

  list_sources (self);

  if (!parse_clips (self)) {
    GST_ERROR ("Couldn't find clips markup in the xptv file");
    return FALSE;
  }

  if (!parse_track_elements (self)) {
    GST_ERROR ("Couldn't find track objects markup in the xptv file");
    return FALSE;
  }


  if (!g_hash_table_size (priv->clips_table) && GES_FORMATTER (self)->project) {
    ges_project_set_loaded (GES_FORMATTER (self)->project,
        GES_FORMATTER (self));
  } else {
    if (!make_clips (self)) {
      GST_ERROR ("Couldn't deserialise the project properly");
      return FALSE;
    }
  }

  xmlXPathFreeContext (priv->xpathCtx);
  xmlFreeDoc (doc);
  return ret;
}
