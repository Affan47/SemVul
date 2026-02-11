MayMergeSpans(Span *span, Span *other) {
  if (aggressive_decommit_) {
    return other->location != Span::IN_USE;
  }
  return span->location == other->location;
}
