netsnmp_subtree_join(netsnmp_subtree *root)
{
    netsnmp_subtree *s, *tmp, *c, *d;

    while (root != NULL) {
        s = root->next;
        while (s != NULL && root->reginfo == s->reginfo) {
            tmp = s->next;
            DEBUGMSGTL(("subtree", "root start "));
            DEBUGMSGOID(("subtree", root->start_a, root->start_len));
            DEBUGMSG(("subtree", " (original end "));
            DEBUGMSGOID(("subtree", root->end_a, root->end_len));
            DEBUGMSG(("subtree", ")\n"));
            DEBUGMSGTL(("subtree", "  JOINING to "));
            DEBUGMSGOID(("subtree", s->start_a, s->start_len));

	    SNMP_FREE(root->end_a);
	    root->end_a   = s->end_a;
            root->end_len = s->end_len;
	    s->end_a      = NULL;

            for (c = root; c != NULL; c = c->children) {
                netsnmp_subtree_change_next(c, s->next);
            }
            for (c = s; c != NULL; c = c->children) {
                netsnmp_subtree_change_prev(c, root);
            }
            DEBUGMSG(("subtree", " so new end "));
            DEBUGMSGOID(("subtree", root->end_a, root->end_len));
            DEBUGMSG(("subtree", "\n"));


            for (c = s->children; c != NULL; c = d) {
                d = c->children;
                netsnmp_subtree_free(c);
            }
            netsnmp_subtree_free(s);
            s = tmp;
        }
        root = root->next;
    }
}
