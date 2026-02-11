xml_parse_markup_circle_node (xmlNodePtr          markup_node,
                              lglTemplateFrame   *frame)
{
        gdouble     x0, y0, r;
        xmlNodePtr  node;

        x0 = lgl_xml_get_prop_length (markup_node, "x0", 0);
        y0 = lgl_xml_get_prop_length (markup_node, "y0", 0);
        r  = lgl_xml_get_prop_length (markup_node, "radius", 0);

        lgl_template_frame_add_markup (frame, lgl_template_markup_circle_new (x0, y0, r));

        for (node = markup_node->xmlChildrenNode; node != NULL; node = node->next)
        {
                if (!xmlNodeIsText (node))
                {
                        if (!lgl_xml_is_node (node, "comment"))
                        {
                                g_message ("bad node =  \"%s\"",node->name);
                        }
                }
        }

}
