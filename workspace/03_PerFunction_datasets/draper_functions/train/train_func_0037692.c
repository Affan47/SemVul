gvir_config_object_get_attribute_genum(GVirConfigObject *object,
                                       const char *node_name,
                                       const char *attr_name,
                                       GType enum_type,
                                       gint default_value)
{
    xmlNodePtr node;
    const char *attr_val;
    gint value;

    g_return_val_if_fail(attr_name != NULL, default_value);

    node = gvir_config_object_get_xml_node(GVIR_CONFIG_OBJECT(object));
    if (node == NULL)
        return default_value;

    if (node_name != NULL) {
        node = gvir_config_xml_get_element(node, node_name, NULL);
        if (node == NULL)
            return default_value;
    }

    attr_val = gvir_config_xml_get_attribute_content(node, attr_name);
    if (attr_val == NULL)
        return default_value;

    value = gvir_config_genum_get_value(enum_type, attr_val,
                                        default_value);

    return value;
}
