li_vector(li_object *lst) {
    li_object *obj;
    li_object *iter;
    int k;

    for (k = 0, iter = lst; iter; k++, iter = li_cdr(iter))
        ;
    obj = li_create(LI_T_VECTOR);
    obj->data.vector.data = li_allocate(li_null, k,
            sizeof(*obj->data.vector.data));
    obj->data.vector.length = k;
    for (k = 0, iter = lst; iter; k++, iter = li_cdr(iter))
        li_vector_set(obj, k, li_car(iter));
    return obj;
}
