make_elem_list(RfmArray array, TypeDict type_dict)
{
    RfmElem  elem;

    if ((array == NULL) || (type_dict == NULL)) {
        return NULL;
    }
    array->dim = 0;
    while (type_dict->type_kind == TKIND_ARRAY) {
        array->dim++;
        elem = MakeArrayRfmElem(array, NULL);
        elem->limit_val = LIMIT_VAL_FROM_TYPE_DICT(type_dict);
        type_dict = type_dict->TYPE_ELEMENT_TYPE;
    }
    return(type_dict);
}
