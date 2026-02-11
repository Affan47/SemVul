see_lm(Lm *lm, int kind)
{
    int i;
    if (cmp_ya_templ) {
        List *li;
        for (li = lm->ya_slot_list[kind]; li != NULL; li = li->next) {
            Slot *slot = li->data;
            fprintf(stderr, "(%d:%d)", slot->slot_no, slot->group_info->local_du->entry);
        }
    } else {
        int slot_num = get_slot_num(lm, kind);
        for (i = 0; i < slot_num; i++) {
            Slot *slot = get_slot(lm, kind, i);
            if (!slot->is_empty && slot->group_info != NULL) {
                fprintf(stderr, "(%d:%d) ", slot->slot_no, slot->group_info->local_du->entry);
            }
        }
    }
    fprintf(stderr, "\n");
}
