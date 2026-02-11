jmp(NearLabel* L) {
  EnsureSpace ensure_space(this);
  last_pc_ = pc_;
  if (L->is_bound()) {
    const int short_size = sizeof(int8_t);
    int offs = L->pos() - pc_offset();
    ASSERT(offs <= 0);
    ASSERT(is_int8(offs - short_size));

    emit(0xEB);
    emit((offs - short_size) & 0xFF);
  } else {
    emit(0xEB);
    emit(0x00);
    L->link_to(pc_offset());
  }
}
