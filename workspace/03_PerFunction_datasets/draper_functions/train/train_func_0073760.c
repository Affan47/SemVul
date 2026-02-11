future_parse(PyFutureFeatures *ff, mod_ty mod, PyObject *filename)
{
    int i, done = 0, prev_line = 0;
    stmt_ty first;

    if (!(mod->kind == Module_kind || mod->kind == Interactive_kind))
        return 1;

    if (asdl_seq_LEN(mod->v.Module.body) == 0)
        return 1;


    i = 0;
    first = (stmt_ty)asdl_seq_GET(mod->v.Module.body, i);
    if (first->kind == Expr_kind && first->v.Expr.value->kind == Str_kind)
        i++;


    for (; i < asdl_seq_LEN(mod->v.Module.body); i++) {
        stmt_ty s = (stmt_ty)asdl_seq_GET(mod->v.Module.body, i);

        if (done && s->lineno > prev_line)
            return 1;
        prev_line = s->lineno;


        if (s->kind == ImportFrom_kind) {
            identifier modname = s->v.ImportFrom.module;
            if (modname &&
                !PyUnicode_CompareWithASCIIString(modname, "__future__")) {
                if (done) {
                    PyErr_SetString(PyExc_SyntaxError,
                                    ERR_LATE_FUTURE);
                    PyErr_SyntaxLocationObject(filename, s->lineno, s->col_offset);
                    return 0;
                }
                if (!future_check_features(ff, s, filename))
                    return 0;
                ff->ff_lineno = s->lineno;
            }
            else {
                done = 1;
            }
        }
        else {
            done = 1;
        }
    }
    return 1;
}
