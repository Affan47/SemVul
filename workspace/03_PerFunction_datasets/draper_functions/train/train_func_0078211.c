ompcbe_write_loop_tmp_for_hetero(csbe_context *cx, Quadruple *qr)
{
    Quadruple *qptr;
    for (qptr = qr; qptr->prev != NULL; qptr = qptr->prev);
    for (; qptr != qr; qptr = qptr->next) {
	csbe_push_quadruple_to_expr(cx, qptr);
    }
    csbe_write_expr(cx, cx->expr_link);

}
