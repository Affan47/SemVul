binary_insert(symtab_entry *p, symtab_entry *e)
{
    int r = strcmp(p->id, e->id);
    if (r < 0) {

        if (p->left == NULL) {
            p->left = e;
            e->parent = p;
        }
        else {
            binary_insert(p->left, e);
        }
    }
    else if (r > 0) {

        if (p->right == NULL) {
            p->right = e;
            e->parent = p;
        }
        else {
            binary_insert(p->right, e);
        }
    }
    else {

    }
}
