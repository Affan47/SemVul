avl_next(struct avl_node *node)
{
    if (node == NULL) return NULL;

#ifdef _AVL_NEXT_POINTER
    return node->next;
#else

    struct avl_node *p;


    if (node->right) {
        p = node;
        node = node->right;
        while (node) {
            p = node;
            node = node->left;
        }
        return p;
    }


    if (avl_parent(node)) {

        p = node;
        node = avl_parent(node);
        while(node) {
            if (node->left == p) {
                return node;
            }
            p = node;
            node = avl_parent(node);
        }
    }
#endif
    return NULL;
}
