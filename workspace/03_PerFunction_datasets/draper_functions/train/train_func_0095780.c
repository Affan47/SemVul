parse_group (xmlNodePtr node, InputPadGroup **pgroup)
{
    xmlNodePtr current;
    gboolean has_name = FALSE;
    gboolean has_table = FALSE;
    InputPadTable **ptable = &((*pgroup)->table);

    for (current = node; current; current = current->next) {
        if (current->type == XML_ELEMENT_NODE) {
            if (!g_strcmp0 ((char *) current->name, "name")) {
                if (current->children) {
                    get_content (current->children, &(*pgroup)->name, TRUE);
                    has_name = TRUE;
                } else {
                    g_error ("tag %s does not have child tags in the file %s",
                             (char *) current->name,
                             xml_file);
                }
            }
            if (!g_strcmp0 ((char *) current->name, "table")) {
                if (current->children) {
                    *ptable = g_new0 (InputPadTable, 1);
                    (*ptable)->priv = g_new0 (InputPadTablePrivate, 1);
                    (*ptable)->column = 15;
                    parse_table (current->children, ptable);
                    ptable = &((*ptable)->next);
                    has_table = TRUE;
                } else {
                    g_error ("tag %s does not have child tags in the file %s",
                             (char *) current->name,
                             xml_file);
                }
            }
        }
    }
    if (!has_name || !has_table ) {
        g_error ("tag %s does not find \"name\" or \"table\" tag in file %s",
                 node->parent ? node->parent->name ? (char *) node->parent->name : "(null)" : "(null)",
                 xml_file);
    }
}
