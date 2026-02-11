tableiter_new(tableobject *table, tableselectfunc select)
{
    tableiterobject *ti;
    ti = PyObject_NEW(tableiterobject, &MpTableIter_Type);
    if (ti == NULL)
        return NULL;
    Py_INCREF(table);
    ti->table = table;
    ti->ti_nelts = table->table->a.nelts;
    ti->ti_pos = 0;
    ti->ti_select = select;
    return (PyObject *)ti;
}
