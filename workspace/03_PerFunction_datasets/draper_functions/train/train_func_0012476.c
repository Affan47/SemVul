array_add_value (context_t *ctx,
                            yajl_val array, yajl_val value)
{
    yajl_val *tmp;


    assert (ctx != NULL);
    assert (array != NULL);
    assert (value != NULL);


    assert(YAJL_IS_ARRAY(array));

    tmp = realloc(array->u.array.values,
                  sizeof(*(array->u.array.values)) * (array->u.array.len + 1));
    if (tmp == NULL)
        RETURN_ERROR(ctx, ENOMEM, "Out of memory");
    array->u.array.values = tmp;
    array->u.array.values[array->u.array.len] = value;
    array->u.array.len++;

    return 0;
}
