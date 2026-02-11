_get_photoset_from_node                 (xmlNode *node)
{
  FspDataPhotoSet *photoSet = NULL;
  xmlChar *content = NULL;
  xmlChar *id = NULL;
  xmlChar *primaryPhotoId = NULL;
  xmlChar *numPhotos = NULL;

  g_return_val_if_fail (node != NULL, NULL);

  if (g_strcmp0 ((gchar *) node->name, "photoset"))
    return NULL;

  id = xmlGetProp (node, (const xmlChar *) "id");
  primaryPhotoId = xmlGetProp (node, (const xmlChar *) "primary");
  numPhotos = xmlGetProp (node, (const xmlChar *) "photos");


  photoSet = FSP_DATA_PHOTO_SET (fsp_data_new (FSP_PHOTO_SET));
  photoSet->id = g_strdup ((gchar *) id);
  photoSet->primary_photo_id = g_strdup ((gchar *) primaryPhotoId);
  if (numPhotos != NULL)
    photoSet->n_photos = (gint) g_ascii_strtoll ((gchar *) numPhotos, NULL, 10);

  xmlFree (id);
  xmlFree (primaryPhotoId);
  xmlFree (numPhotos);


  for (node = node->children; node != NULL; node = node->next)
    {
      if (node->type != XML_ELEMENT_NODE)
        continue;


      if (!g_strcmp0 ((gchar *) node->name, "title"))
        {
          content = xmlNodeGetContent (node);
          photoSet->title = g_strdup ((gchar *) content);
          xmlFree (content);
        }


      if (!g_strcmp0 ((gchar *) node->name, "description"))
        {
          content = xmlNodeGetContent (node);
          photoSet->description = g_strdup ((gchar *) content);
          xmlFree (content);
        }
    }

  return photoSet;
}
