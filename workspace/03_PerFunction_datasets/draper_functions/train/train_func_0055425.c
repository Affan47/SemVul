GetNextRange(PageID start, base::MallocRange* r) {
  Span* span = reinterpret_cast<Span*>(pagemap_.Next(start));
  if (span == NULL) {
    return false;
  }
  r->address = span->start << kPageShift;
  r->length = span->length << kPageShift;
  r->fraction = 0;
  switch (span->location) {
    case Span::IN_USE:
      r->type = base::MallocRange::INUSE;
      r->fraction = 1;
      if (span->sizeclass > 0) {

        const size_t osize = Static::sizemap()->class_to_size(span->sizeclass);
        r->fraction = (1.0 * osize * span->refcount) / r->length;
      }
      break;
    case Span::ON_NORMAL_FREELIST:
      r->type = base::MallocRange::FREE;
      break;
    case Span::ON_RETURNED_FREELIST:
      r->type = base::MallocRange::UNMAPPED;
      break;
    default:
      r->type = base::MallocRange::UNKNOWN;
      break;
  }
  return true;
}
