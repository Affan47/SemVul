GC_finalize()
{
    struct finalizable_object * curr_fo, * prev_fo, * next_fo;
    ptr_t real_ptr;
    register int i;
    int fo_size = (log_fo_table_size == -1 ) ? 0 : (1 << log_fo_table_size);


	GC_make_disappearing_links_disappear(&GC_dl_hashtbl);


    GC_ASSERT(GC_mark_state == MS_NONE);
    for (i = 0; i < fo_size; i++) {
      for (curr_fo = fo_head[i]; curr_fo != 0; curr_fo = fo_next(curr_fo)) {
        real_ptr = (ptr_t)REVEAL_POINTER(curr_fo -> fo_hidden_base);
        if (!GC_is_marked(real_ptr)) {
	    GC_MARKED_FOR_FINALIZATION(real_ptr);
            GC_MARK_FO(real_ptr, curr_fo -> fo_mark_proc);
            if (GC_is_marked(real_ptr)) {
                WARN("Finalization cycle involving %lx\n", real_ptr);
            }
        }
      }
    }


    GC_words_finalized = 0;
    for (i = 0; i < fo_size; i++) {
      curr_fo = fo_head[i];
      prev_fo = 0;
      while (curr_fo != 0) {
        real_ptr = (ptr_t)REVEAL_POINTER(curr_fo -> fo_hidden_base);
        if (!GC_is_marked(real_ptr)) {
	    if (!GC_java_finalization) {
              GC_set_mark_bit(real_ptr);
	    }

              next_fo = fo_next(curr_fo);
              if (prev_fo == 0) {
                fo_head[i] = next_fo;
              } else {
                fo_set_next(prev_fo, next_fo);
              }
              GC_fo_entries--;

              fo_set_next(curr_fo, GC_finalize_now);
              GC_finalize_now = curr_fo;


              curr_fo -> fo_hidden_base =
              		(word) REVEAL_POINTER(curr_fo -> fo_hidden_base);
              GC_words_finalized +=
                 	ALIGNED_WORDS(curr_fo -> fo_object_size)
              		+ ALIGNED_WORDS(sizeof(struct finalizable_object));
	    GC_ASSERT(GC_is_marked(GC_base((ptr_t)curr_fo)));
            curr_fo = next_fo;
        } else {
            prev_fo = curr_fo;
            curr_fo = fo_next(curr_fo);
        }
      }
    }

  if (GC_java_finalization) {


      for (curr_fo = GC_finalize_now;
  	 curr_fo != NULL; curr_fo = fo_next(curr_fo)) {
  	real_ptr = (ptr_t)curr_fo -> fo_hidden_base;
  	if (!GC_is_marked(real_ptr)) {
  	    if (curr_fo -> fo_mark_proc == GC_null_finalize_mark_proc) {
  	        GC_MARK_FO(real_ptr, GC_normal_finalize_mark_proc);
  	    }
  	    GC_set_mark_bit(real_ptr);
  	}
      }
  }


  GC_remove_dangling_disappearing_links(&GC_dl_hashtbl);


  GC_make_disappearing_links_disappear(&GC_ll_hashtbl);
  GC_remove_dangling_disappearing_links(&GC_ll_hashtbl);
}
