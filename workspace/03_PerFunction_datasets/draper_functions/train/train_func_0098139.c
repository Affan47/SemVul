GC_push_marked2(struct hblk *h, hdr *hhdr)
{
    word * mark_word_addr = &(hhdr->hb_marks[0]);
    word *p;
    word *plim;
    word *q;
    word mark_word;

    ptr_t greatest_ha = GC_greatest_plausible_heap_addr;
    ptr_t least_ha = GC_least_plausible_heap_addr;
    mse * mark_stack_top = GC_mark_stack_top;
    mse * mark_stack_limit = GC_mark_stack_limit;

#   define GC_mark_stack_top mark_stack_top
#   define GC_mark_stack_limit mark_stack_limit
#   define GC_greatest_plausible_heap_addr greatest_ha
#   define GC_least_plausible_heap_addr least_ha

    p = (word *)(h->hb_body);
    plim = (word *)(((word)h) + HBLKSIZE);


        while (p < plim) {
            mark_word = *mark_word_addr++;
            q = p;
            while(mark_word != 0) {
              if (mark_word & 1) {
                  PUSH_GRANULE(q);
                  PUSH_GRANULE(q + GC_GRANULE_WORDS);
              }
              q += 2 * GC_GRANULE_WORDS;
              mark_word >>= 2;
            }
            p += WORDSZ*GC_GRANULE_WORDS;
        }

#   undef GC_greatest_plausible_heap_addr
#   undef GC_least_plausible_heap_addr
#   undef GC_mark_stack_top
#   undef GC_mark_stack_limit

    GC_mark_stack_top = mark_stack_top;
}
