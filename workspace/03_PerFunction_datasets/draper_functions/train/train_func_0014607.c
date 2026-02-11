gupnp_device_info_list_device_types (GUPnPDeviceInfo *info)
{
        GList *device_types;
        xmlNode *element;

        g_return_val_if_fail (GUPNP_IS_DEVICE_INFO (info), NULL);

        device_types = NULL;

        element = xml_util_get_element (info->priv->element,
                                        "deviceList",
                                        NULL);
        if (!element)
                return NULL;

        for (element = element->children; element; element = element->next) {
                if (!strcmp ("device", (char *) element->name)) {
                        char *type;

                        type = xml_util_get_child_element_content_glib
                                                   (element, "deviceType");
                        if (!type)
                                continue;

                        device_types = g_list_prepend (device_types, type);
                }
        }

        return device_types;
}
