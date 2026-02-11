discard_empty_slot_for_slot_pool(Lm *lm, Module_table *module, Block *b, const int pgno,
                                 Stasche_lm_dt *sld, const int kind)
{
    int mt_num = sld->mt_num;
    List *li;
    List *next;

    for (li = lm->ya_slot_list[kind]; li != NULL; li = next) {
        Slot *slot = li->data;

        next = li->next;
        if (slot_is_empty(slot, mt_num)) {
            clear_slot(slot, module->array_head, sld->mt_num, sld);
        }
    }
}
