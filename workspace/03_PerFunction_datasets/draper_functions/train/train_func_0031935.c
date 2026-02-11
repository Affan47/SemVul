darray_resize(darray_t *array, size_t newsize)
{
    array->max = newsize;
    array->contents = h_realloc(array->contents, array->max * sizeof(void *));
    check_mem(array->contents);
    return 0;
error:
    return -1;
}
