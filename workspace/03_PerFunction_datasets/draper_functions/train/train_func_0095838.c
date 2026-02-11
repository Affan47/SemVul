collect_subexpression_of_dosum_sum(Quadruple *qr,
				   Quadruple *top,
				   int       ope_num)
{
    int       total, count;
    Quadruple *qpt;
    Operand   **temparray;
    Operand   **tmparytmp;

    total=0;
    total += count_temp_in_operand(qr->op[ope_num]);

    if (total==0) {
        return;
    }
    temparray = (Operand **)malloc(total*sizeof(Operand *));
    tmparytmp = temparray;
    temp_collection(qr->op[ope_num], &tmparytmp);

    for (count = total-1 ; count>=0 ; count--) {
        for (qpt = qr->prev; qpt; qpt=qpt->prev) {
            if (qpt->op[0]
             && qpt->op[0]->kind == KIND_TEMP
             && qpt->op[0]->entry == temparray[count]->entry) {
                collect_subexpression(qpt, top);
            }
        }
    }
}
