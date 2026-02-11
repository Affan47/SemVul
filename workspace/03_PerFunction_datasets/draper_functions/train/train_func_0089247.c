astproc_walk_recursive(astnode *n, void *arg, const astnodeprocmap *map, astnode **next)
{
    astnode *c;
    astnode *t;
    if (n == NULL) { return; }
    astnodeproc p = astproc_node_type_to_proc(astnode_get_type(n), map);
    if (p != NULL) {
        if (!p(n, arg, next))
            return;
    }

    for (c=n->first_child; c != NULL; c = t) {
        t = c->next_sibling;
        astproc_walk_recursive(c, arg, map, &t);
    }
}
