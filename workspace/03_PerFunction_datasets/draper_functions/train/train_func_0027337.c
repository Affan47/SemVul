symtable_visit_alias(struct symtable *st, alias_ty a)
{


    PyObject *store_name;
    PyObject *name = (a->asname == NULL) ? a->name : a->asname;
    const char *base = PyString_AS_STRING(name);
    char *dot = strchr(base, '.');
    if (dot) {
        store_name = PyString_FromStringAndSize(base, dot - base);
        if (!store_name)
            return 0;
    }
    else {
        store_name = name;
        Py_INCREF(store_name);
    }
    if (strcmp(PyString_AS_STRING(name), "*")) {
        int r = symtable_add_def(st, store_name, DEF_IMPORT);
        Py_DECREF(store_name);
        return r;
    }
    else {
        if (st->st_cur->ste_type != ModuleBlock) {
        int lineno = st->st_cur->ste_lineno;
        if (!symtable_warn(st, IMPORT_STAR_WARNING, lineno)) {
            Py_DECREF(store_name);
            return 0;
        }
        }
        st->st_cur->ste_unoptimized |= OPT_IMPORT_STAR;
        Py_DECREF(store_name);
        return 1;
    }
}
