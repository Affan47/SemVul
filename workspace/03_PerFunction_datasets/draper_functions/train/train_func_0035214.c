cpu_set_richcompare(Py_cpu_set *set, Py_cpu_set *other, int op)
{
    int eq;

    if ((op != Py_EQ && op != Py_NE) || Py_TYPE(other) != &cpu_set_type)
        Py_RETURN_NOTIMPLEMENTED;

    eq = set->ncpus == other->ncpus && CPU_EQUAL_S(set->size, set->set, other->set);
    if ((op == Py_EQ) ? eq : !eq)
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}
