arrayiter_next(arrayiterobject *it)
{
    assert(PyArrayIter_Check(it));
    if (it->index < Py_SIZE(it->ao))
        return (*it->getitem)(it->ao, it->index++);
    return NULL;
}
