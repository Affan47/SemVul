append_acc_table(Acc_table *apt)
{
    Acc_table *ptr;
    ptr = acc_head;
    if (ptr == NULL) {
        acc_head = apt;
    } else {
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        apt->prev = ptr;
        ptr->next = apt;
    }
}
