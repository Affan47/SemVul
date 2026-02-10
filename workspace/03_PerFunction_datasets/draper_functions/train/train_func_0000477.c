add_child(struct cross_elem *word, struct strie_pair *new_child)
{
    struct strie_pair *cur_child = NULL;

    if (!word)
        return 1;

    if (!word->firstchild)
    {
        word->firstchild = new_child;
        return 0;
    }

    cur_child = word->firstchild;
    while (cur_child->brother)
    {
        cur_child = cur_child->brother;
    }
    cur_child->brother = new_child;
    return 0;
}
