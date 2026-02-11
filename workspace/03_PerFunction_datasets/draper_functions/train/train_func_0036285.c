setup_func(xmlNodePtr node)
{
    xmlNodePtr n;
    Options *o;

    o = g_slice_new0(Options);
    o->dir = OB_DIRECTION_NORTH;
    o->shrink = FALSE;

    if ((n = obt_xml_find_node(node, "direction"))) {
        gchar *s = obt_xml_node_string(n);
        if (!g_ascii_strcasecmp(s, "north") ||
            !g_ascii_strcasecmp(s, "up"))
            o->dir = OB_DIRECTION_NORTH;
        else if (!g_ascii_strcasecmp(s, "south") ||
                 !g_ascii_strcasecmp(s, "down"))
            o->dir = OB_DIRECTION_SOUTH;
        else if (!g_ascii_strcasecmp(s, "west") ||
                 !g_ascii_strcasecmp(s, "left"))
            o->dir = OB_DIRECTION_WEST;
        else if (!g_ascii_strcasecmp(s, "east") ||
                 !g_ascii_strcasecmp(s, "right"))
            o->dir = OB_DIRECTION_EAST;
        g_free(s);
    }

    return o;
}
