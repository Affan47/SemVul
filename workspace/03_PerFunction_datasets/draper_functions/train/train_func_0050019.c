parse_focus(xmlNodePtr node, gpointer d)
{
    xmlNodePtr n;

    node = node->children;

    if ((n = obt_xml_find_node(node, "focusNew")))
        config_focus_new = obt_xml_node_bool(n);
    if ((n = obt_xml_find_node(node, "followMouse")))
        config_focus_follow = obt_xml_node_bool(n);
    if ((n = obt_xml_find_node(node, "focusDelay")))
        config_focus_delay = obt_xml_node_int(n);
    if ((n = obt_xml_find_node(node, "raiseOnFocus")))
        config_focus_raise = obt_xml_node_bool(n);
    if ((n = obt_xml_find_node(node, "focusLast")))
        config_focus_last = obt_xml_node_bool(n);
    if ((n = obt_xml_find_node(node, "underMouse")))
        config_focus_under_mouse = obt_xml_node_bool(n);
    if ((n = obt_xml_find_node(node, "unfocusOnLeave")))
        config_unfocus_leave = obt_xml_node_bool(n);
}
