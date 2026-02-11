append_operand(Operand **op_head, Operand *op)
{
    Operand *opt;

    if (*op_head == NULL) {
        *op_head = op;
    } else {
        for (opt = (*op_head); opt->next != NULL; opt = opt->next)
            ;

        opt->next = op;
    }
}
