get_quadruple_from_operand_in_block(Block *block, Operand *op)
{
    Quadruple *qr;


    qr = get_quadruple_from_operand_in_pe_stms(block->pre_head, op);
    if (qr == NULL) {
        qr = get_quadruple_from_operand_in_pe_stms(block->post_head, op);
    }

    return qr;
}
