xmlnode_child(xmlnode *node)
{
    xmlnode *head = NULL;
    xmlnode *tail = NULL;
    xmlnode *new;
    xmlNode *cnode;

    if (node->child) {
        return node->child;
    }

    cnode = node->node->xmlChildrenNode;

    while (cnode) {

        new          = g_new0(xmlnode, 1);
        new->node    = cnode;
        new->is_root = 0;
        new->doc     = node->doc;
        new->name    = g_strdup((gchar*)cnode->name);
        new->parent  = node;
        new->child   = NULL;
        new->next    = NULL;

        if (!head) {
            head = new;
            tail = new;

        } else {
            tail->next = new;
            tail = new;
        }

        cnode = cnode->next;
    }

    node->child = head;

    return head;
}
