dict_lookup_rect(Object *dict,
                             const char *key,
                             float rect[4])
{
    Object o;
    Array *array;
    int i;

    if (!dict->dictLookup(key, &o))
        return false;

    if (!o.isArray()) {
        o.free();
        return false;
    }

    array = o.getArray();
    for (i = 0; i < 4; i++) {
        Object el;
        if (array->get(i, &el) && el.isNum())
            rect[i] = el.getNum();
        el.free();
    }

    o.free();
    return i == 4;
}
