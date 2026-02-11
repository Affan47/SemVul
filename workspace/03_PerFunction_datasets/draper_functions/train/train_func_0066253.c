chain_reduce(chainobject *lz)
{
    if (lz->source) {


        if (lz->active) {
            return Py_BuildValue("O()(OO)", Py_TYPE(lz), lz->source, lz->active);
        } else {
            return Py_BuildValue("O()(O)", Py_TYPE(lz), lz->source);
        }
    } else {
        return Py_BuildValue("O()", Py_TYPE(lz));
    }
    return NULL;
}
