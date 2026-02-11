sort_discard_slot(Lm *lm, Block *b, Stasche_lm_dt *sld, const int kind,
                  IntSet used_slot)
{
    List *head = NULL;
    int slot_num = get_slot_num(lm, kind);
    int i;

    for (i = 0; i < slot_num; i++) {
        if (used_slot == NULL || !in_IntSet(used_slot, i)) {
            Slot *slot = get_slot(lm, kind, i);
            slot->dpri = calc_discard_priority(slot, sld, b);
            head = list_append(head, slot);
        }
    }

    list_sort(head, cmp_slot_dpri);

    return head;
}
