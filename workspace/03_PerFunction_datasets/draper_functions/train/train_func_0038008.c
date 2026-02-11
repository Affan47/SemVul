VisitPointers(Object** start, Object** end) {
    for (Object** p = start; p < end; p++) {
      if (!known_references_ || !known_references_->Contains(*p)) {
        generator_->SetHiddenReference(parent_obj_, parent_, next_index_++, *p);
      }
    }
  }
