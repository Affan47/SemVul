PySymtable_Build(mod_ty mod, const char *filename, PyFutureFeatures *future)
{
    struct symtable *st;
    asdl_seq *seq;
    int i;

    if (__class__ == NULL) {
        __class__ = PyUnicode_InternFromString("@__class__");
        if (__class__ == NULL)
            return NULL;
    }

    st = symtable_new();
    if (st == NULL)
        return st;
    st->st_filename = filename;
    st->st_future = future;

    if (!GET_IDENTIFIER(top) ||
        !symtable_enter_block(st, top, ModuleBlock, (void *)mod, 0, 0)) {
        PySymtable_Free(st);
        return NULL;
    }

    st->st_top = st->st_cur;
    st->st_cur->ste_unoptimized = OPT_TOPLEVEL;
    switch (mod->kind) {
    case Module_kind:
        seq = mod->v.Module.body;
        for (i = 0; i < asdl_seq_LEN(seq); i++)
            if (!symtable_visit_stmt(st,
                        (stmt_ty)asdl_seq_GET(seq, i)))
                goto error;
        break;
    case Expression_kind:
        if (!symtable_visit_expr(st, mod->v.Expression.body))
            goto error;
        break;
    case Interactive_kind:
        seq = mod->v.Interactive.body;
        for (i = 0; i < asdl_seq_LEN(seq); i++)
            if (!symtable_visit_stmt(st,
                        (stmt_ty)asdl_seq_GET(seq, i)))
                goto error;
        break;
    case Suite_kind:
        PyErr_SetString(PyExc_RuntimeError,
                        "this compiler does not handle Suites");
        goto error;
    }
    if (!symtable_exit_block(st, (void *)mod)) {
        PySymtable_Free(st);
        return NULL;
    }

    if (symtable_analyze(st))
        return st;
    PySymtable_Free(st);
    return NULL;
 error:
    (void) symtable_exit_block(st, (void *)mod);
    PySymtable_Free(st);
    return NULL;
}
