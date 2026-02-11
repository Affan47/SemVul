_dwarf_p_get_alloc(Dwarf_P_Debug dbg, Dwarf_Unsigned size)
{
    void *sp;
    memory_list_t *lp = NULL;
    memory_list_t *dbglp = NULL;
    memory_list_t *nextblock = NULL;


    lp = (memory_list_t *) malloc(size + sizeof(memory_list_t));
    if (lp == NULL) {

        return NULL;
    }


    sp = LIST_TO_BLOCK(lp);
    memset(sp, 0, size);

    if (dbg == NULL) {
        lp->next = lp->prev = lp;
    } else {


        dbglp = BLOCK_TO_LIST(dbg);
        nextblock = dbglp->next;


        dbglp->next = lp;
        lp->prev = dbglp;
        lp->next = nextblock;
        nextblock->prev = lp;
    }

    return sp;
}
