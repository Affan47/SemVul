GC_new_free_list_inner()
{
    void *result = GC_INTERNAL_MALLOC((MAXOBJSZ+1)*sizeof(ptr_t), PTRFREE);
    if (result == 0) ABORT("Failed to allocate freelist for new kind");
    BZERO(result, (MAXOBJSZ+1)*sizeof(ptr_t));
    return result;
}
