uninit_partitions(struct partition *head)
{

    fastfw_list(head);

    struct partition *current = head;
    struct partition *prev = NULL;

    while(current != NULL) {
        prev = current->prevp;
        free(current);
        current = prev;
    }
    return;
}
