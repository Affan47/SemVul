postorderNonRecursive(BinarySearchTreeNode* root) {
    BinarySearchTreeNode* current = root;
    while (current) {
        if (current->left && !current->left->visited) {
            current = current->left;
            continue;
        } else if (current->right && !current->right->visited) {
            current = current->right;
            continue;
        }

        if (!current->visited) {
            current->print();
            current->visited = true;
        }

        if (current->left)
            current->left->visited = false;
        if (current->right)
            current->right->visited = false;

        current = current->parent;
    };
    if (root)
        root->visited = false;
}
