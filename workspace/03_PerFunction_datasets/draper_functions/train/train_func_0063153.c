fsbe_write_data_node(fsbe_context *cx, Data_table *data, Data_node *node)
{
    switch(operand_type(data->op)) {
    case TYPE_INT:
        fsbe_printf(cx, "%d", node->val.i);
        break;
    case TYPE_REAL:
        fsbe_printf(cx, "%.16E", (node->type == TYPE_REAL)
                    ? node->val.r : node->val.d);
        break;
    case TYPE_DOUBLE:
        fsbe_write_const_double(cx, node->val.d);
        break;
    case TYPE_CHARACTER:
        fsbe_printf(cx, "'%s'", node->val.s);
        break;
    case TYPE_LOGICAL:
        if (node->val.l)
            fsbe_printf(cx, ".TRUE.");
        else
            fsbe_printf(cx, ".FALSE.");
        break;
    case TYPE_COMPLEX:
        fsbe_printf(cx, "(");
        fsbe_printf(cx, "%.16E", (node->type == TYPE_COMPLEX)
                    ? node->val.c.re : node->val.dc.re);
        fsbe_printf(cx, ",");
        fsbe_printf(cx, "%.16E", (node->type == TYPE_COMPLEX)
                    ? node->val.c.im : node->val.dc.im);
        fsbe_printf(cx, ")");
        break;
    case TYPE_DCOMPLEX:
        fsbe_printf(cx, "(");
        fsbe_write_const_double(cx, node->val.dc.re);
        fsbe_printf(cx, ",");
        fsbe_write_const_double(cx, node->val.dc.im);
        fsbe_printf(cx, ")");
        break;
    default:
        fatal("[NOT IMPLEMENTED]\n");
    }
}
