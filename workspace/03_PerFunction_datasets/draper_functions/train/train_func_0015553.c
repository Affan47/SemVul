acc_dir2qr(Module_table *mpt, Statement *stm, Directive *dir_stm,
	   qr_operator ope)
{
    Statement *acc_stm = NULL;
    Statement *spt;
    Quadruple*  qpt;

    for (spt = stm->pe_stm->stm_head; spt != NULL; spt = spt->next) {
        if (spt->ope == ope) {
            acc_stm = spt;
            break;
        }
    }
    if (acc_stm == NULL) {
        acc_stm = alloc_statement();
        acc_stm->ope = ope;
        acc_stm->line_no = dir_stm->line_no;
        if (stm->ope != OPE_LABEL) {
            insert_stm(stm->pe_stm, stm->prev, acc_stm);
        } else {
            insert_stm(stm->pe_stm, stm, acc_stm);
        }
    }

    switch (ope) {
    case  OPE_ASSIGN_DRP:
	make_drp_qr(mpt, acc_stm, dir_stm->func->opt);
	break;
    case  OPE_ASSIGN_ACC:
	make_acc_qr(mpt, acc_stm, dir_stm->func->opt);
	break;
    default:
	fatal("Illegal hetero operator.");
    }
    for (qpt = acc_stm->qr_head; qpt != NULL; qpt = qpt->next) {
        qpt->stm = acc_stm;
    }
}
