obt_xml_attr_string(xmlNodePtr node, const gchar *name,
                             gchar **value)
{
    gboolean result = obt_xml_attr_string_unstripped(node, name, value);
    if (result)
        g_strstrip(*value);
    return result;
}
