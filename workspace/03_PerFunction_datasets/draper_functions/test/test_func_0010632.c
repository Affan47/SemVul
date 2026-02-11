right_rotate(ompi_rb_tree_t *tree, ompi_rb_tree_node_t * x)
{
    ompi_rb_tree_node_t * y;

    y = x->left;

    if(y->right != tree->nill) {
        y->right->parent = x;
    }

    if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->parent = x->parent;
    x->parent = y;
    x->left = y->right;
    y->right = x;

    return;
}
