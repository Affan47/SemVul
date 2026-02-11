DeleteAll() {
#ifdef DEBUG

  static const unsigned char kZapDeadByte = 0xcd;
#endif


  Segment* keep = Segment::head();
  while (keep != NULL && keep->size() > kMaximumKeptSegmentSize) {
    keep = keep->next();
  }


  Segment* current = Segment::head();
  while (current != NULL) {
    Segment* next = current->next();
    if (current == keep) {

      current->clear_next();
    } else {
      int size = current->size();
#ifdef DEBUG

      memset(current, kZapDeadByte, size);
#endif
      Segment::Delete(current, size);
    }
    current = next;
  }


  if (keep != NULL) {
    Address start = keep->start();
    position_ = RoundUp(start, kAlignment);
    limit_ = keep->end();
#ifdef DEBUG

    memset(start, kZapDeadByte, keep->capacity());
#endif
  } else {
    position_ = limit_ = 0;
  }


  Segment::set_head(keep);
}
