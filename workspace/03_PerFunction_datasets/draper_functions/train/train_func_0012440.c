change_array_qr(Quadruple *qr_head, int entry, Array_table *apt)
{
    Quadruple   *qpt;
    int         i;

    qpt = qr_head;
    while (qpt != NULL) {
        for (i = 0; i < 4; i++)
            change_array_operand(qpt->op[i], entry, apt);
        qpt = qpt->next;
    }
}
