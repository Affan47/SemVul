list_free(list_t *root)
{
    list_t *l = root;
    while (root)
    {
        l = root;
        root = root->next;
        free(l);
    }
}
