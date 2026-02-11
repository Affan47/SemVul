set_label_for_multi(Block *target, Block *ifbpt)
{
    Statement  *tspt, *spt;
    Quadruple  *tqpt;
    Operand    *opt = NULL;

    tspt = ifbpt->pre_head->stm_head;
    while (tspt != NULL) {
        if (tspt->ope == OPE_JF) {
            tqpt = tspt->qr_head;
            while(tqpt){
                if(tqpt->ope == OPE_JF){
                    opt = copy_operand(tqpt->op[0]);
                    break;
                }
                tqpt = tqpt->next;
            }
            break;
        }
        tspt = tspt->next;
    }

    spt = alloc_label_stm_for_multi(opt);
    spt->next = target->pre_head->stm_head;
    target->pre_head->stm_head->prev = spt;
    target->pre_head->stm_head = spt;
    spt->pe_stm = target->pre_head;
}
