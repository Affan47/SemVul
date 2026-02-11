append_acc_mtg_table(Acc_mtg_table *mtg, Acc_table *apt)
{
    Acc_mtg_table *ptr;
    ptr = apt->mtg_head;
    if (ptr == NULL) {
        apt->mtg_head = mtg;
    } else {
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        mtg->prev = ptr;
        ptr->next = mtg;
    }
}
