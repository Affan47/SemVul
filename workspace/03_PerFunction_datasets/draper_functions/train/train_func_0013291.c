search_and_get_pa_object_op(Operand *op, Pa_info *pa_info, Module_table *mpt)
{
    Pa_object *obj, *o;
    Pa_object *pa_object_list = pa_info->head;

    obj = search_pa_object_op(op, pa_object_list);

    if (obj == NULL) {
        if (pa_info->ptr_flg == TRUE) {
            pa_info->head = copy_pa_object_list(pa_info->head);
            pa_info->ptr_flg = FALSE;
            pa_object_list = pa_info->head;
        }

        obj = make_pa_object_op(mpt, op);
        for (o = pa_object_list; o->next != NULL; o = o->next);
        o->next = obj;
    }

    return obj;
}
