didl_item_available_cb (GUPnPDIDLLiteParser *parser,
                        GUPnPDIDLLiteObject *object,
                        gpointer             user_data)
{
        GList *resources;
        GUPnPDIDLLiteResource *resource;
        const char **import_uri = (const char **) user_data;

        if (*import_uri != NULL) {


                return;
        }

        resources = gupnp_didl_lite_object_get_resources (object);
        if (resources == NULL) {
                return;
        }

        resource = (GUPnPDIDLLiteResource *) resources->data;

        *import_uri = gupnp_didl_lite_resource_get_import_uri(resource);
        if (*import_uri != NULL) {
                *import_uri = g_strdup (*import_uri);
        }

        while (resources) {
                g_object_unref ((GUPnPDIDLLiteResource *) resources->data);
                resources = g_list_delete_link (resources, resources);
        }
}
