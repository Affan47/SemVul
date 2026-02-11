efreet_menu_handle_layout_merge(Efreet_Menu_Internal *parent, Efreet_Xml *xml, int def)
{
    Efreet_Menu_Layout *layout;
    const char *attr;

    if (!parent || !xml) return 0;

    attr = efreet_xml_attribute_get(xml, "type");
    if (!attr)
    {
        INF("efreet_menu_handle_layout_merge() The Merge tag in layout "
                "needs a type attribute.");
        return 0;
    }

    if (strcmp(attr, "files") && strcmp(attr, "menus") && strcmp(attr, "all"))
    {
        INF("efreet_menu_handle_layout_merge() The type attribute for "
                "the Merge tag contains an unknown value (%s).", attr);
        return 0;
    }

    layout = efreet_menu_layout_new();
    layout->type = EFREET_MENU_LAYOUT_MERGE;
    layout->name = eina_stringshare_add(attr);

    if (def) parent->default_layout = eina_list_append(parent->default_layout, layout);
    else parent->layout = eina_list_append(parent->layout, layout);

    return 1;
}
