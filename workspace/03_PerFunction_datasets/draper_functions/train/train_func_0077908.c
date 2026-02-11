accumulate_reduce(accumulateobject *lz)
{
    return Py_BuildValue("O(OO)O", Py_TYPE(lz),
                            lz->it, lz->binop?lz->binop:Py_None,
                            lz->total?lz->total:Py_None);
 }
