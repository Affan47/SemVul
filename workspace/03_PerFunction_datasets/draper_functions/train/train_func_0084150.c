back_delete_all(httrackp * opt, cache_back * cache, struct_back * sback) {
  if (sback != NULL) {
    int i;


    for(i = 0; i < sback->count; i++) {
      back_delete(opt, cache, sback, i);
    }

    if (sback->ready != NULL) {
      struct_inthash_enum e = inthash_enum_new(sback->ready);
      inthash_chain *item;

      while((item = inthash_enum_next(&e))) {
#ifndef HTS_NO_BACK_ON_DISK
        char *filename = (char *) item->value.ptr;

        if (filename != NULL) {
          (void) UNLINK(filename);
        }
#else

        lien_back *back = (lien_back *) item->value.ptr;

        back_clear_entry(back);
#endif
      }

      inthash_delete(&sback->ready);
      sback->ready_size_bytes = 0;
    }
  }
}
