backtrack(int *tick, bool *cleared_exit,
                            struct course **cend,
                            struct frame **lfrend) {
    --*tick;
    struct course *prev = (*cend)->prev;
    if (prev == NULL) {
        struct xyz pos = (*cend)->pos;
        errexit('x', "Aieee.  Plane at (%d, %d, %d) is impossible.",
                pos.row, pos.col, pos.alt);
    }
    struct xyz rv = prev->pos;
    *cleared_exit = prev->cleared_exit;
    free(*cend);
    *cend = prev;
    prev->next = NULL;

    struct frame *fr = *lfrend;
    *lfrend = fr->prev;
    (*lfrend)->next = NULL;
    free_op_courses(fr->opc_start);
    free(fr);

    return rv;
}
