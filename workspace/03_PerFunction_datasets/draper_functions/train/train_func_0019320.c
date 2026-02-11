get_last_used_kind(Lm *lm)
{
    int i;
    for (i = lm->max_kind; i >= 0; i--) {
        if (is_slot_used(lm, i)) {
            return i;
        }
    }
    return i;
}
