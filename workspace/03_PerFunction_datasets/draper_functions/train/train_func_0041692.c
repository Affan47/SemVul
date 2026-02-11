removeNode(BinarySearchTreeNode *node) {
    BinarySearchTreeNode *newRoot, *temp;
    if (node->right) {
        newRoot = node->right;
        newRoot->parent = node->parent;
        if (node->parent) {
            if (node->parent->right == node)
                node->parent->right = newRoot;
            else
                node->parent->left = newRoot;
        } else
            root = newRoot;
        temp = findSubtreeMin(newRoot);
        temp->left = node->left;
        if (node->left)
            node->left->parent = temp;
    } else if (node->left) {
        newRoot = node->left;
        newRoot->parent = node->parent;
        if (node->parent) {
            if (node->parent->right == node)
                node->parent->right = newRoot;
            else
                node->parent->left = newRoot;
        } else
            root = newRoot;
        temp = findSubtreeMax(newRoot);
        temp->right = node->right;
        if (node->right)
            node->right->parent = temp;
    } else {
        if (node->parent) {
            if (node->parent->right == node)
                node->parent->right = 0;
            else
                node->parent->left = 0;
        } else
            root = 0;
    }
    delete node;
}
