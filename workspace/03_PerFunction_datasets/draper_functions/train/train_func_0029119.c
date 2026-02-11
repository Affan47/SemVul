setup_func(xmlNodePtr node,
                           ObActionsIPreFunc *pre,
                           ObActionsIInputFunc *input,
                           ObActionsICancelFunc *cancel,
                           ObActionsIPostFunc *post)
{
    xmlNodePtr n;
    Options *o;

    o = g_slice_new0(Options);

    o->type = ABSOLUTE;
    o->u.abs.desktop = screen_desktop;

    o->u.rel.wrap = TRUE;

    if ((n = obt_xml_find_node(node, "to"))) {
        gchar *s = obt_xml_node_string(n);
        if (!g_ascii_strcasecmp(s, "last"))
            o->type = LAST;
        else if (!g_ascii_strcasecmp(s, "current"))
            o->type = CURRENT;
        else if (!g_ascii_strcasecmp(s, "next")) {
            o->type = RELATIVE;
            o->u.rel.linear = TRUE;
            o->u.rel.dir = OB_DIRECTION_EAST;
        }
        else if (!g_ascii_strcasecmp(s, "previous")) {
            o->type = RELATIVE;
            o->u.rel.linear = TRUE;
            o->u.rel.dir = OB_DIRECTION_WEST;
        }
        else if (!g_ascii_strcasecmp(s, "north") ||
                 !g_ascii_strcasecmp(s, "up")) {
            o->type = RELATIVE;
            o->u.rel.dir = OB_DIRECTION_NORTH;
        }
        else if (!g_ascii_strcasecmp(s, "south") ||
                 !g_ascii_strcasecmp(s, "down")) {
            o->type = RELATIVE;
            o->u.rel.dir = OB_DIRECTION_SOUTH;
        }
        else if (!g_ascii_strcasecmp(s, "west") ||
                 !g_ascii_strcasecmp(s, "left")) {
            o->type = RELATIVE;
            o->u.rel.dir = OB_DIRECTION_WEST;
        }
        else if (!g_ascii_strcasecmp(s, "east") ||
                 !g_ascii_strcasecmp(s, "right")) {
            o->type = RELATIVE;
            o->u.rel.dir = OB_DIRECTION_EAST;
        }
        else {
            o->type = ABSOLUTE;
            o->u.abs.desktop = atoi(s) - 1;
        }
        g_free(s);
    }

    if ((n = obt_xml_find_node(node, "wrap")))
        o->u.rel.wrap = obt_xml_node_bool(n);

    return o;
}
