list_findpos(const list_t *restrict l, int posstart) {
    struct list_entry_s *ptr;
    float x;
    int i;


    if (posstart < -1 || posstart > (int)l->numels) return NULL;

    x = (float)(posstart+1) / l->numels;
    if (x <= 0.25) {

        for (i = -1, ptr = l->head_sentinel; i < posstart; ptr = ptr->next, i++);
    } else if (x < 0.5) {

        for (i = (l->numels-1)/2, ptr = l->mid; i > posstart; ptr = ptr->prev, i--);
    } else if (x <= 0.75) {

        for (i = (l->numels-1)/2, ptr = l->mid; i < posstart; ptr = ptr->next, i++);
    } else {

        for (i = l->numels, ptr = l->tail_sentinel; i > posstart; ptr = ptr->prev, i--);
    }

    return ptr;
}
