search_temp_qr(const Operand *op, Quadruple *qr)
{
    Quadruple *qr_s;
    Operand **t_op;
    for (qr_s = qr; qr_s != NULL; qr_s = qr_s->next) {
	    t_op = search_operand(op, qr_s);
	    if (t_op != NULL)
		return qr_s;
    }

    return NULL;
}
