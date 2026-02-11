left_neighbour_leaf(GBT_TREE *node) {
    if (node) {
        GBT_TREE *father = node->father;
        while (father) {
            if (father->rightson==node) {
                node = rightmost_leaf(father->leftson);
                nt_assert(node->is_leaf);
                if (!node->gb_node) {
                    node = left_neighbour_leaf(node);
                }
                return node;
            }
            node = father;
            father = node->father;
        }
    }
    return 0;
}
