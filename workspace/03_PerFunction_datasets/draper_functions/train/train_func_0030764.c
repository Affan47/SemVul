GC_add_to_fl(struct hblk *h, hdr *hhdr)
{
    int index = GC_hblk_fl_from_blocks(divHBLKSZ(hhdr -> hb_sz));
    struct hblk *second = GC_hblkfreelist[index];
    hdr * second_hdr;
#   if defined(GC_ASSERTIONS) && !defined(USE_MUNMAP)
      struct hblk *next = (struct hblk *)((word)h + hhdr -> hb_sz);
      hdr * nexthdr = HDR(next);
      struct hblk *prev = GC_free_block_ending_at(h);
      hdr * prevhdr = HDR(prev);
      GC_ASSERT(nexthdr == 0 || !HBLK_IS_FREE(nexthdr)
                || (signed_word)GC_heapsize < 0);

      GC_ASSERT(prev == 0 || !HBLK_IS_FREE(prevhdr)
                || (signed_word)GC_heapsize < 0);
#   endif

    GC_ASSERT(((hhdr -> hb_sz) & (HBLKSIZE-1)) == 0);
    GC_hblkfreelist[index] = h;
    GC_free_bytes[index] += hhdr -> hb_sz;
    GC_ASSERT(GC_free_bytes[index] <= GC_large_free_bytes);
    hhdr -> hb_next = second;
    hhdr -> hb_prev = 0;
    if (0 != second) {
      GET_HDR(second, second_hdr);
      second_hdr -> hb_prev = h;
    }
    hhdr -> hb_flags |= FREE_BLK;
}
