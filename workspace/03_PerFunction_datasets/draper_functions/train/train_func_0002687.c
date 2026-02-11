delete(struct node *root, int value) {
    struct node *node, *nodeParent, *nodeAux;
    int aux, nChild;

    node = search(root, value);
    if(!node)
        return ERROR;

    nChild = node->left && node->right ? node->left || node->right ? 2 : 1 : 0;
    if(nChild < 2) {
        nodeParent = searchParent(root, value);
        if(nodeParent) {
            if(nodeParent->left && nodeParent->left->value == node->value)
                nodeParent->left = nChild ? node->left ? node->left : node->right : NULL;
            else
                nodeParent->right = nChild ? node->left ? node->left : node->right : NULL;
        }
        else
            node->value = 0;
        free(node);
    }
    else {
        nodeAux = findMost(node->right, LEFT);
        aux = nodeAux->value;
        delete(node, aux);
        node->value = aux;
    }

    return SUCCESS;
}
