slot_is_empty(Slot *slot, const int mt_num)
{
    int i;

    if (slot->is_empty) {
        return TRUE;
    }

    if (slot->fd_list != NULL) {
        return FALSE;
    }
    for (i = 1; i <= mt_num; i++) {
        if (!empty_IntSet(slot->iset[i])
            || !empty_IntSet(slot->bset[i])
            || !empty_IntSet(slot->oset[i])) {
            return FALSE;
        }
    }

    return TRUE;
}
