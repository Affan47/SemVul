disconnect_inv_stm(Loop_inv_stm * inv_stm)
{
    Loop_inv_stm * temp;

    if (inv_stm_head == NULL || inv_stm == NULL) {
        return ;
    }
    if (inv_stm_head == inv_stm) {
        if (inv_stm_head == inv_stm_tail) {
            inv_stm_head = NULL;
            inv_stm_tail = NULL;
            return ;
        }
        inv_stm_head = inv_stm->next;
        inv_stm->next = NULL;
        return ;
    }
    for (temp = inv_stm_head; temp != NULL; temp = temp->next) {
        if (temp->next == inv_stm) {
            if (temp->next == inv_stm_tail) {
                inv_stm_tail = temp;
            }
            temp->next = inv_stm->next;
            inv_stm->next = NULL;
            break;
        }
    }
    return ;
}
