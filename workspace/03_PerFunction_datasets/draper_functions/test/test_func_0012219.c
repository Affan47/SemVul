set_label_info(Block *branch_bpt, Block *label_bpt, Label_table *lt)
{
    Quadruple *qrpt;

    lt->qr = label_bpt->pre_head->stm_head->qr_head;
    lt->qr->op[0]->tbl.l = lt;
    lt->qr->op[0]->entry = lt->label_no;

    qrpt = branch_bpt->pre_head->stm_head->qr_head;

    for (; qrpt->next != NULL; qrpt = qrpt->next);

    qrpt->branch = lt->qr;
    qrpt->op[0]->tbl.l = lt;
    qrpt->op[0]->entry = lt->label_no;
}
