Scavenge() {


  for (int cl = 0; cl < kNumClasses; cl++) {
    FreeList* list = &list_[cl];
    const int lowmark = list->lowwatermark();
    if (lowmark > 0) {
      const int drop = (lowmark > 1) ? lowmark/2 : 1;
      ReleaseToCentralCache(list, cl, drop);


      const int batch_size = Static::sizemap()->num_objects_to_move(cl);
      if (list->max_length() > batch_size) {
        list->set_max_length(
            max<int>(list->max_length() - batch_size, batch_size));
      }
    }
    list->clear_lowwatermark();
  }

  IncreaseCacheLimit();
}
