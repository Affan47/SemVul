bintree_create(const char *file, bintree_t **root)
{
    int         in;
    bintree_t  *node;

    if (!root) {
        return EPARAM2;
    }

    if (freopen(file, "r", stdin) == NULL) {
        printf("%d\n", strerror(errno));
        return ESYSCALL;
    }

    while (scanf("%d", &in) != EOF) {
        node = malloc(sizeof(bintree_t));
        if (!node) {
            fclose(stdin);
            return ENOMEMORY;
        }

        node->data = in;
        node->left = node->right = NULL;

        if (*root == NULL) {
            *root = node;
            continue;
        }

        bintree_insert(*root, node);
    }

    fclose(stdin);

    return OK;
}
