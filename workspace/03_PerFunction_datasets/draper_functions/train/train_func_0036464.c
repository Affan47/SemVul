construct_array_usage(Array_subscript_info *asi,
                      int ndim,
                      AccessType *type,
                      Operand *index,
		      Pa_object *pa_object)
{
    ArrayUsage *au;

    au = (ArrayUsage *)malloc(sizeof(ArrayUsage));
    if (au == NULL)
        fatal("alloc failded\n");

    au->entry = asi->entry;
    au->kind = asi->kind;
    au->ndim = ndim;
    au->type = type;
    au->index = au_detect_align_dim_index(asi, ndim, type, index);
    au->pa_object = pa_object;

    return au;
}
