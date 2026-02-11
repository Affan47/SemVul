ref_array_get(struct ref_array *ra, uint32_t idx, void *acptr)
{
    TRACE_FLOW_ENTRY();

    if (!ra) {
        TRACE_ERROR_STRING("Uninitialized argument.", "");
        return NULL;
    }

    if (idx >= ra->len) {
        TRACE_INFO_NUMBER("Invalid idx.", idx);
        return NULL;
    }

    TRACE_INFO_NUMBER("Index: ", idx);

    if (acptr) {

        TRACE_INFO_STRING("Copying data.", "");
        memcpy(acptr,
               (unsigned char *)(ra->storage) + idx * ra->elsize,
               ra->elsize);

    }

    TRACE_FLOW_EXIT();
    return (unsigned char *)(ra->storage) + idx * ra->elsize;
}
