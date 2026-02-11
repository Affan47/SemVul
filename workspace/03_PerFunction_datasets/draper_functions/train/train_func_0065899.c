GC_freehblk(struct hblk *hbp)
{
    struct hblk *next, *prev;
    hdr *hhdr, *prevhdr, *nexthdr;
    signed_word size;

    GET_HDR(hbp, hhdr);
    size = hhdr->hb_sz;
    size = HBLKSIZE * OBJ_SZ_TO_BLOCKS(size);
    if (size <= 0)
      ABORT("Deallocating excessively large block.  Too large an allocation?");


    GC_remove_counts(hbp, (word)size);
    hhdr->hb_sz = size;
#   ifdef USE_MUNMAP
      hhdr -> hb_last_reclaimed = (unsigned short)GC_gc_no;
#   endif


      if (HBLK_IS_FREE(hhdr)) {
        if (GC_print_stats)
          GC_log_printf("Duplicate large block deallocation of %p\n", hbp);
        ABORT("Duplicate large block deallocation");
      }

    GC_ASSERT(IS_MAPPED(hhdr));
    hhdr -> hb_flags |= FREE_BLK;
    next = (struct hblk *)((word)hbp + size);
    GET_HDR(next, nexthdr);
    prev = GC_free_block_ending_at(hbp);

      if(0 != nexthdr && HBLK_IS_FREE(nexthdr) && IS_MAPPED(nexthdr)
         && (signed_word)(hhdr -> hb_sz + nexthdr -> hb_sz) > 0
         ) {
        GC_remove_from_fl(nexthdr, FL_UNKNOWN);
        hhdr -> hb_sz += nexthdr -> hb_sz;
        GC_remove_header(next);
      }

      if (0 != prev) {
        prevhdr = HDR(prev);
        if (IS_MAPPED(prevhdr)
            && (signed_word)(hhdr -> hb_sz + prevhdr -> hb_sz) > 0) {
          GC_remove_from_fl(prevhdr, FL_UNKNOWN);
          prevhdr -> hb_sz += hhdr -> hb_sz;
#         ifdef USE_MUNMAP
            prevhdr -> hb_last_reclaimed = (unsigned short)GC_gc_no;
#         endif
          GC_remove_header(hbp);
          hbp = prev;
          hhdr = prevhdr;
        }
      }


    GC_large_free_bytes += size;
    GC_add_to_fl(hbp, hhdr);
}
