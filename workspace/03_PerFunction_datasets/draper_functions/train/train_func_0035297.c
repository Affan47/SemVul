discard_possible_slot(Lm* lm, const int targetno)
{
    int i;

    for (i = 0; i < lm->slot_num; i++) {
        if (can_discard_slot(lm->slot[i], targetno)) {
            return lm->slot[i];
        }
    }

    return NULL;
}
