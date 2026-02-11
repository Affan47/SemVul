gupnp_didl_lite_object_get_title_xml_string (GUPnPDIDLLiteObject *object)
{
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_OBJECT (object), NULL);

        return xml_util_get_child_string (object->priv->xml_node,
                                          object->priv->xml_doc->doc,
                                          "title");
}
