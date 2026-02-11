cpl_xmemory_free(void * ptr)
{

    size_t pos;


    if (ptr == NULL) return;

    if (cpl_xmemory_ncells == 0) {
        fprintf(stderr, "cpl_xmemory error: Ignoring free() on unallocated "
                "pointer (%p)\n", ptr);
        return;
    }


    pos = cpl_xmemory_findcell(ptr);

    if (pos == cpl_xmemory_table_size) {
        fprintf(stderr, "cpl_xmemory error: Ignoring free() on unallocated "
                "pointer (%p)\n", ptr);
        return;

    }


    free(ptr);


#   ifdef _OPENMP
#   pragma omp atomic
#   endif
    cpl_xmemory_ncells--;

    if (cpl_xmemory_ncells > 0) {

        cpl_xmemory_remcell(pos);
    } else {

        cpl_xmemory_end();
    }

    return;
}
