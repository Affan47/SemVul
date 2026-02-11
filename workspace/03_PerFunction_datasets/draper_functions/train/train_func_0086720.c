compiler_comprehension(struct compiler *c, expr_ty e, int type, identifier name,
                       asdl_seq *generators, expr_ty elt, expr_ty val)
{
    PyCodeObject *co = NULL;
    expr_ty outermost_iter;

    outermost_iter = ((comprehension_ty)
                      asdl_seq_GET(generators, 0))->iter;

    if (!compiler_enter_scope(c, name, (void *)e, e->lineno))
        goto error;

    if (type != COMP_GENEXP) {
        int op;
        switch (type) {
        case COMP_SETCOMP:
            op = BUILD_SET;
            break;
        case COMP_DICTCOMP:
            op = BUILD_MAP;
            break;
        default:
            PyErr_Format(PyExc_SystemError,
                         "unknown comprehension type %d", type);
            goto error_in_scope;
        }

        ADDOP_I(c, op, 0);
    }

    if (!compiler_comprehension_generator(c, generators, 0, elt,
                                          val, type))
        goto error_in_scope;

    if (type != COMP_GENEXP) {
        ADDOP(c, RETURN_VALUE);
    }

    co = assemble(c, 1);
    compiler_exit_scope(c);
    if (co == NULL)
        goto error;

    if (!compiler_make_closure(c, co, 0))
        goto error;
    Py_DECREF(co);

    VISIT(c, expr, outermost_iter);
    ADDOP(c, GET_ITER);
    ADDOP_I(c, CALL_FUNCTION, 1);
    return 1;
error_in_scope:
    compiler_exit_scope(c);
error:
    Py_XDECREF(co);
    return 0;
}
