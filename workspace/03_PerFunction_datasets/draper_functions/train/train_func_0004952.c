printOrder(struct node *root, int order) {
    if(PRE_ORDER == order)
        printf("%d ", root->value);
    if(root->left)
        printOrder(root->left, order);
    if(IN_ORDER == order)
        printf("%d ", root->value);
    if(root->right)
        printOrder(root->right, order);
    if(POST_ORDER == order)
        printf("%d ", root->value);
}
