wmem_test_allocator_det(wmem_allocator_t *allocator, wmem_verify_func verify,
        guint len)
{
    int i;
    char *ptrs[MAX_SIMULTANEOUS_ALLOCS];


    for (i=0; i<MAX_SIMULTANEOUS_ALLOCS; i++) {
        ptrs[i] = (char *)wmem_alloc0(allocator, len);
    }
    for (i=MAX_SIMULTANEOUS_ALLOCS-1; i>=0; i--) {

        ptrs[i] = (char *)wmem_realloc(allocator, ptrs[i], 4*len);
        memset(ptrs[i], 0, 4*len);
    }
    for (i=0; i<MAX_SIMULTANEOUS_ALLOCS; i++) {
        wmem_free(allocator, ptrs[i]);
    }

    if (verify) (*verify)(allocator);
    wmem_free_all(allocator);
    wmem_gc(allocator);
    if (verify) (*verify)(allocator);
}
