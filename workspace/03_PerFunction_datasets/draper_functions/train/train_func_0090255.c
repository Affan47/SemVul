GC_enqueue_all_finalizers(void)
  {
    struct finalizable_object * curr_fo, * prev_fo, * next_fo;
    ptr_t real_ptr;
    register int i;
    int fo_size;

    fo_size = log_fo_table_size == -1 ? 0 : 1 << log_fo_table_size;
    GC_bytes_finalized = 0;
    for (i = 0; i < fo_size; i++) {
        curr_fo = GC_fo_head[i];
        prev_fo = 0;
      while (curr_fo != 0) {
          real_ptr = GC_REVEAL_POINTER(curr_fo -> fo_hidden_base);
          GC_MARK_FO(real_ptr, GC_normal_finalize_mark_proc);
          GC_set_mark_bit(real_ptr);


          next_fo = fo_next(curr_fo);
          if (prev_fo == 0) {
              GC_fo_head[i] = next_fo;
          } else {
              fo_set_next(prev_fo, next_fo);
          }
          GC_fo_entries--;


          fo_set_next(curr_fo, GC_finalize_now);
          GC_finalize_now = curr_fo;


          curr_fo -> fo_hidden_base =
                        (word)GC_REVEAL_POINTER(curr_fo -> fo_hidden_base);
          GC_bytes_finalized +=
                curr_fo -> fo_object_size + sizeof(struct finalizable_object);
          curr_fo = next_fo;
        }
    }
  }
