maybe_add_guid (xmlNodePtr ptr, const char *tag, GncTaxTable *table)
{
    if (table)
        xmlAddChild (ptr, guid_to_dom_tree (tag,
                                            qof_instance_get_guid(QOF_INSTANCE(table))));
}
