GC_unprotect_range(addr, len)
ptr_t addr;
word len;
{
    struct hblk * start_block;
    struct hblk * end_block;
    register struct hblk *h;
    ptr_t obj_start;

    if (!GC_dirty_maintained) return;
    obj_start = GC_base(addr);
    if (obj_start == 0) return;
    if (GC_base(addr + len - 1) != obj_start) {
        ABORT("GC_unprotect_range(range bigger than object)");
    }
    start_block = (struct hblk *)((word)addr & ~(GC_page_size - 1));
    end_block = (struct hblk *)((word)(addr + len - 1) & ~(GC_page_size - 1));
    end_block += GC_page_size/HBLKSIZE - 1;
    for (h = start_block; h <= end_block; h++) {
        register word index = PHT_HASH(h);

        async_set_pht_entry_from_index(GC_dirty_pages, index);
    }
    UNPROTECT(start_block,
    	      ((ptr_t)end_block - (ptr_t)start_block) + HBLKSIZE);
}
