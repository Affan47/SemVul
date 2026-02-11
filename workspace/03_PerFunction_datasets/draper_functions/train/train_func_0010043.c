fsbe_write_arithmetic_if_hook(cx, qp, lbl_m, lbl_z, lbl_p)
    fsbe_context *cx;
    Quadruple *qp;
    Operand *lbl_m;
    Operand *lbl_z;
    Operand *lbl_p;
{
    Quadruple *qp_m = NULL;
    Quadruple *qp_z = NULL;
    Quadruple *qp_p = NULL;
    Quadruple *qp0;

    for (qp0 = qp; qp0 != NULL; qp0 = qp0->next) {
        if (qp0->op[0] == lbl_m) {
            qp_m = qp0;
        }
        if (qp0->op[0] == lbl_z) {
            qp_z = qp0;
        }
        if (qp0->op[0] == lbl_p) {
            qp_p = qp0;
        }
    }

    ompfbe_iprintf(cx, "IF(");
    fsbe_write_operand(cx, qp->op[1]);
    fsbe_printf(cx, ".LT.0) THEN\n");

    if (lbl_m->kind == KIND_MT) {
        ompfbe_increment_indent_level();
        ompfbe_write_mt_jump(cx, qp_m->stm, qp_m);
        ompfbe_decrement_indent_level();
    } else {
        ompfbe_iprintf(cx, "GOTO ");
        fsbe_write_operand(cx, lbl_m);
        fsbe_printf(cx, "\n");
    }

    ompfbe_iprintf(cx, "ELSE IF(");
    fsbe_write_operand(cx, qp->op[1]);
    fsbe_printf(cx, ".EQ.0) THEN\n");

    if (lbl_z->kind == KIND_MT) {
        ompfbe_increment_indent_level();
        ompfbe_write_mt_jump(cx, qp_z->stm, qp_z);
        ompfbe_decrement_indent_level();
    } else {
        ompfbe_iprintf(cx, "GOTO ");
        fsbe_write_operand(cx, lbl_z);
        fsbe_printf(cx, "\n");
    }

    ompfbe_iprintf(cx, "ELSE\n");

    if (lbl_p->kind == KIND_MT) {
        ompfbe_increment_indent_level();
        ompfbe_write_mt_jump(cx, qp_p->stm, qp_p);
        ompfbe_decrement_indent_level();
    } else {
        ompfbe_iprintf(cx, "GOTO ");
        fsbe_write_operand(cx, lbl_p);
        fsbe_printf(cx, "\n");
    }
    ompfbe_iprintf(cx, "END IF\n");

    return 1;
}
