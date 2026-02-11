get_quadruple_from_operand_in_pe_stms(Pe_statement *head, Operand *op)
{
    int i;
    Pe_statement *pe_stm;
    Statement *stm;
    Quadruple *qr;

    for(pe_stm = head; pe_stm; pe_stm = pe_stm->next) {
        for(stm = pe_stm->stm_head; stm; stm = stm->next){
            for(qr = stm->qr_head; qr; qr = qr->next) {
                for(i = 0; i < 4; i++) {
                    if(qr->op[i] != NULL && qr->op[i] == op) {
                        return qr;
                    }
                }
            }
        }
    }
    return NULL;
}
