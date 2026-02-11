tst_grow_node_free_list(struct tst *tst)
{
    struct node *current_node;
    struct node_lines *new_line;
    int i;

    new_line = xmalloc(sizeof(struct node_lines));
    new_line->node_line = xcalloc(tst->node_line_width, sizeof(struct node));
    new_line->next = tst->node_lines;
    tst->node_lines = new_line;

    current_node = tst->node_lines->node_line;
    tst->free_list = current_node;
    for (i = 1; i < tst->node_line_width; i++) {
        current_node->middle = &(tst->node_lines->node_line[i]);
        current_node = current_node->middle;
    }
    current_node->middle = NULL;
}
