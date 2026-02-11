xmlnode_next(xmlnode *node)
{
    xmlnode *new;

    g_return_val_if_fail(node != NULL, NULL);

    new = node->next;

    return new;
}
