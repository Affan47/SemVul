inorder_traversal(ompi_rb_tree_t *tree,
                              ompi_rb_tree_condition_fn_t cond,
                              ompi_rb_tree_action_fn_t action,
                              ompi_rb_tree_node_t * node)
{
    if (node == tree->nill) {
        return;
    }

    inorder_traversal(tree, cond, action, node->left);

    if (cond(node->value)) {
        action(node->key, node->value);
    }

    inorder_traversal(tree, cond, action, node->right);
}
