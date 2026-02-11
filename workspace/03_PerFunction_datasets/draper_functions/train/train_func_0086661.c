parse_command (xmlNodePtr node, InputPadTableCmd *cmd)
{
    xmlNodePtr current;
    gboolean has_execl = FALSE;

    for (current = node; current; current = current->next) {
        if (current->type == XML_ELEMENT_NODE) {
            if (!g_strcmp0 ((char *) current->name, "label")) {
                if (current->children) {
                    get_content (current->children, &cmd->label, TRUE);
                } else {
                    g_error ("tag %s does not have child tags in the file %s",
                             (char *) current->name,
                             xml_file);
                }
            }
            if (!g_strcmp0 ((char *) current->name, "execl")) {
                if (current->children) {
                    get_content (current->children, &cmd->execl, FALSE);
                    has_execl = TRUE;
                } else {
                    g_error ("tag %s does not have child tags in the file %s",
                             (char *) current->name,
                             xml_file);
                }
            }
        }
    }
    if (!has_execl) {
        g_error ("tag %s does not find \"execl\" tag in file %s",
                 node->parent ? node->parent->name ? (char *) node->parent->name : "(null)" : "(null)",
                 xml_file);
    }
}
