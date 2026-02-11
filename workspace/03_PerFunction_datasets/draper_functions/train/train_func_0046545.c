GC_alloc_large_and_clear(lw, k, flags)
word lw;
int k;
unsigned flags;
{
    ptr_t result = GC_alloc_large(lw, k, flags);
    word n_blocks = OBJ_SZ_TO_BLOCKS(lw);

    if (0 == result) return 0;
    if (GC_debugging_started || GC_obj_kinds[k].ok_init) {

	BZERO(result, n_blocks * HBLKSIZE);
    }
    return result;
}
