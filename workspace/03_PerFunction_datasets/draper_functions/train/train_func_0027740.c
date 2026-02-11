bstnode_init(long key, void *data, bstnode *parent)
{
    bstnode *n, *l, *r;
    n = malloc(sizeof *n);
    l = malloc(sizeof *n);
    r = malloc(sizeof *n);

    if (!n || !l || !r)
    {
        free(n);
        free(l);
        free(r);
        return NULL;
    }

    n->key = key;
    n->color = RED;
    n->data = data;
    n->parent = parent;

    n->left = l;
    n->right = r;
    l->color = r->color = LEAF;
    l->key = r->key = -1;
    l->parent = r->parent = n;

    return n;
}
