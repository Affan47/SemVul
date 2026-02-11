DArray_resize(DArray *array, size_t newsize)
{
    array->max = newsize;
    check(array->max > 0, "The newsize must be > 0.");
    array->contents = realloc(array->contents, array->max * sizeof(void *));
    check_mem(array->contents);
    return 0;
error:
    return -1;
}
