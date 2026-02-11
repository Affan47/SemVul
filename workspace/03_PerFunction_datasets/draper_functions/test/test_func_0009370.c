astnode_remove_child(astnode *p, astnode *c)
{
    int i;
    i = astnode_get_child_index(p, c);
    if (i == 0) {

        p->first_child = c->next_sibling;
        if (p->first_child) {
            p->first_child->prev_sibling = NULL;
        }
        c->parent = c->next_sibling = c->prev_sibling = NULL;
    }
    else if (i > 0) {
        c->prev_sibling->next_sibling = c->next_sibling;
        if (c->next_sibling) {
            c->next_sibling->prev_sibling = c->prev_sibling;
        }
        c->parent = c->next_sibling = c->prev_sibling = NULL;
    }
    return i;
}
