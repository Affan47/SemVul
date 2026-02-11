mbarray_ClearAll(MBArray * array)
{
    if (!array || !array->vector) {
        errno = EINVAL;
        return 1;
    }
    memset((void *)(array->vector + array->preamblesize), 0, sizeof(DTYPE) * array->size);
    return 0;
}
