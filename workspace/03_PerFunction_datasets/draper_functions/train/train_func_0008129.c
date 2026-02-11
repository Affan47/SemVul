adjust_array_slot_dim_qr(Quadruple *qr_head, int entry, Operand *slot_no,
                         SemTree **offsets)
{
    Quadruple   *qpt;
    int         i;

    qpt = qr_head;
    while (qpt != NULL) {
        if (qpt->ope == OPE_STORE && qpt->prev != NULL
            && qpt->prev->ope == OPE_ASSIGN) {
            if (qpt->op[0]->kind == KIND_ARRAY &&
                qpt->prev->op[0]->kind == KIND_ARRAY &&
                qpt->op[0]->entry == entry &&
                qpt->prev->op[0]->entry == entry) {
                adjust_array_slot_dim_for_assing_store(qpt->op[0], qpt->prev->op[0]);
	    }
	} else {
            for (i = 0; i < 4; i++)
	        adjust_array_slot_dim_operand(qpt->op[i], qpt, entry, slot_no,
                                              offsets);
	}
        qpt = qpt->next;
    }
}
