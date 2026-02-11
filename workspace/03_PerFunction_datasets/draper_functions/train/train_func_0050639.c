cue_list_remove(CueList *list, CueListNode *node)
{
    if (node == list->head) {
        cue_list_shift(list);
    }
    else if (node == list->tail) {
        cue_list_pop(list);
    }
    else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->prev = NULL;
        node->next = NULL;
    }
}
