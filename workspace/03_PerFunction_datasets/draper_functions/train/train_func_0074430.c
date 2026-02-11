GC_init_explicit_typing(void)
{
    register unsigned i;
    DCL_LOCK_STATE;

    GC_STATIC_ASSERT(sizeof(struct LeafDescriptor) % sizeof(word) == 0);
    LOCK();
    if (GC_explicit_typing_initialized) {
      UNLOCK();
      return;
    }
    GC_explicit_typing_initialized = TRUE;

      GC_eobjfreelist = (ptr_t *)GC_new_free_list_inner();
      GC_explicit_kind = GC_new_kind_inner(
                            (void **)GC_eobjfreelist,
                            (((word)WORDS_TO_BYTES(-1)) | GC_DS_PER_OBJECT),
                            TRUE, TRUE);

      GC_typed_mark_proc_index = GC_new_proc_inner(GC_typed_mark_proc);

      GC_arobjfreelist = (ptr_t *)GC_new_free_list_inner();
      GC_array_mark_proc_index = GC_new_proc_inner(GC_array_mark_proc);
      GC_array_kind = GC_new_kind_inner(
                            (void **)GC_arobjfreelist,
                            GC_MAKE_PROC(GC_array_mark_proc_index, 0),
                            FALSE, TRUE);
      for (i = 0; i < WORDSZ/2; i++) {
          GC_descr d = (((word)(-1)) >> (WORDSZ - i)) << (WORDSZ - i);
          d |= GC_DS_BITMAP;
          GC_bm_table[i] = d;
      }
    UNLOCK();
}
