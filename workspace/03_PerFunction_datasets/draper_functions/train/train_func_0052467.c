ref_array_destroy(struct ref_array *ra)
{
    int idx;

    TRACE_FLOW_ENTRY();


    if (!ra) {
        TRACE_INFO_STRING("Uninitialized array.", "Might be Ok...");
        return;
    }

    TRACE_INFO_NUMBER("Current reference count: ", ra->refcount);
    if (ra->refcount) {

        ra->refcount--;
        if (ra->refcount == 0) {
            TRACE_INFO_NUMBER("It is time to delete array. Count:", ra->refcount);
            if (ra->cb) {
                for (idx = 0; idx < ra->len; idx++) {
                    ra->cb((unsigned char *)(ra->storage) + idx * ra->elsize,
                            REF_ARRAY_DESTROY, ra->cb_data);
                }
            }
            free(ra->storage);
            free(ra);
        }
    }
    else {


        TRACE_ERROR_STRING("Reference count is 0.", "Coding error???");
    }

    TRACE_FLOW_EXIT();
}
