AddUsePosition(LifetimePosition pos,
                                       LOperand* operand) {
  LAllocator::TraceAlloc("Add to live range %d use position %d\n",
                         id_,
                         pos.Value());
  UsePosition* use_pos = new UsePosition(pos, operand);
  UsePosition* prev = NULL;
  UsePosition* current = first_pos_;
  while (current != NULL && current->pos().Value() < pos.Value()) {
    prev = current;
    current = current->next();
  }

  if (prev == NULL) {
    use_pos->set_next(first_pos_);
    first_pos_ = use_pos;
  } else {
    use_pos->next_ = prev->next_;
    prev->next_ = use_pos;
  }

  return use_pos;
}
