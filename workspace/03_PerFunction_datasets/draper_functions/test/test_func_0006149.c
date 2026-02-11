compiler_unit_free(struct compiler_unit *u)
{
    basicblock *b, *next;

    compiler_unit_check(u);
    b = u->u_blocks;
    while (b != NULL) {
        if (b->b_instr)
            PyObject_Free((void *)b->b_instr);
        next = b->b_list;
        PyObject_Free((void *)b);
        b = next;
    }
    Py_CLEAR(u->u_ste);
    Py_CLEAR(u->u_name);
    Py_CLEAR(u->u_qualname);
    Py_CLEAR(u->u_consts);
    Py_CLEAR(u->u_names);
    Py_CLEAR(u->u_varnames);
    Py_CLEAR(u->u_freevars);
    Py_CLEAR(u->u_cellvars);
    Py_CLEAR(u->u_private);
    PyObject_Free(u);
}
