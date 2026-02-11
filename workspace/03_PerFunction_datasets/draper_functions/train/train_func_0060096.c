bst_clear(bst *t, void (*callback)(void*))
{
    if (!t || !t->root)
        return;

    bstnode_free(t->root, callback);
    t->root = NULL;
}
