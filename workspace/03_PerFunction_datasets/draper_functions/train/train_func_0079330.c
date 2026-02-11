kui_tree_push_key(struct kui_tree *ktree, int key, int *map_found)
{
    int found;
    struct kui_tree_node *ktnode;

    *map_found = 0;

    if (ktree->state != KUI_TREE_MATCHING)
        return -1;


    if (kui_tree_find(key, ktree->cur->children, &found, &ktnode) == -1)
        return -1;


    if (!found) {
        ktree->state = KUI_TREE_NOT_FOUND;
        ktree->cur = NULL;
        return 0;
    }

    if (found) {
        ktree->cur = ktnode;

        if (std_list_length(ktnode->children) == 0)
            ktree->state = KUI_TREE_FOUND;

        if (ktnode->macro_value) {
            ktree->found = 1;
            ktree->found_node = ktnode;
            *map_found = 1;
        }
    }

    return 0;
}
