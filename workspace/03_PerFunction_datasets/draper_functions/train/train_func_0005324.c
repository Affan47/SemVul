GC_general_register_disappearing_link(void * * link,
                                                         void * obj)
{
    struct disappearing_link *curr_dl;
    size_t index;
    struct disappearing_link * new_dl;
    DCL_LOCK_STATE;

    if (((word)link & (ALIGNMENT-1)) || link == NULL)
        ABORT("Bad arg to GC_general_register_disappearing_link");
    LOCK();
    GC_ASSERT(obj != NULL && GC_base(obj) == obj);
    if (log_dl_table_size == -1
        || GC_dl_entries > ((word)1 << log_dl_table_size)) {
        GC_grow_table((struct hash_chain_entry ***)(&dl_head),
                      &log_dl_table_size);
        if (GC_print_stats) {
            GC_log_printf("Grew dl table to %u entries\n",
                      (1 << (unsigned)log_dl_table_size));
        }
    }
    index = HASH2(link, log_dl_table_size);
    for (curr_dl = dl_head[index]; curr_dl != 0; curr_dl = dl_next(curr_dl)) {
        if (curr_dl -> dl_hidden_link == GC_HIDE_POINTER(link)) {
            curr_dl -> dl_hidden_obj = GC_HIDE_POINTER(obj);
            UNLOCK();
            return GC_DUPLICATE;
        }
    }
    new_dl = (struct disappearing_link *)
        GC_INTERNAL_MALLOC(sizeof(struct disappearing_link),NORMAL);
    if (0 == new_dl) {
      GC_oom_func oom_fn = GC_oom_fn;
      UNLOCK();
      new_dl = (struct disappearing_link *)
                (*oom_fn)(sizeof(struct disappearing_link));
      if (0 == new_dl) {
        return GC_NO_MEMORY;
      }

      LOCK();

      index = HASH2(link, log_dl_table_size);

      for (curr_dl = dl_head[index]; curr_dl != 0;
           curr_dl = dl_next(curr_dl)) {
        if (curr_dl -> dl_hidden_link == GC_HIDE_POINTER(link)) {
          curr_dl -> dl_hidden_obj = GC_HIDE_POINTER(obj);
          UNLOCK();
#         ifndef DBG_HDRS_ALL

            GC_free((void *)new_dl);
#         endif
          return GC_DUPLICATE;
        }
      }
    }
    new_dl -> dl_hidden_obj = GC_HIDE_POINTER(obj);
    new_dl -> dl_hidden_link = GC_HIDE_POINTER(link);
    dl_set_next(new_dl, dl_head[index]);
    dl_head[index] = new_dl;
    GC_dl_entries++;
    UNLOCK();
    return GC_SUCCESS;
}
