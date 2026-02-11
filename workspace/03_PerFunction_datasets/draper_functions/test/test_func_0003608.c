read_state_variable (const char *variable_name,
                     GValue     *value,
                     xmlNode    *instance_node)
{
        xmlNode    *variable_node;
        const char *val_str;

        variable_node = xml_util_get_element (instance_node,
                                              variable_name,
                                              NULL);
        if (!variable_node)
                return FALSE;

        val_str = xml_util_get_attribute_content (variable_node, "val");
        if (!val_str) {
                g_warning ("No value provided for variable \"%s\" in "
                           "LastChange event",
                           variable_name);

                return FALSE;
        }

        gvalue_util_set_value_from_string (value, val_str);

        return TRUE;
}
