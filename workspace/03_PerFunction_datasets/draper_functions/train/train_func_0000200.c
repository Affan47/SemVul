tableiter_next(tableiterobject *ti, PyObject *args)
{
    apr_table_entry_t *elts = (apr_table_entry_t *) ti->table->table->a.elts;


    if (ti->ti_nelts != ti->table->table->a.nelts) {
        PyErr_SetString(PyExc_RuntimeError,
                        "table changed size during iteration");
        return NULL;
    }


    if (ti->ti_pos < ti->table->table->a.nelts) {
        return (*ti->ti_select)(&elts[ti->ti_pos++]);
    }


    PyErr_SetObject(PyExc_StopIteration, Py_None);
    return NULL;
}
