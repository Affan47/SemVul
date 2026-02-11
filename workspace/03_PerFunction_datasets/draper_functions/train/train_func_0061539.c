bind_to(Label* L, int pos) {
  ASSERT(!L->is_bound());
  ASSERT(0 <= pos && pos <= pc_offset());
  if (L->is_linked()) {
    int current = L->pos();
    int next = long_at(current);
    while (next != current) {

      int imm32 = pos - (current + sizeof(int32_t));
      long_at_put(current, imm32);
      current = next;
      next = long_at(next);
    }

    int last_imm32 = pos - (current + sizeof(int32_t));
    long_at_put(current, last_imm32);
  }
  while (L->is_near_linked()) {
    int fixup_pos = L->near_link_pos();
    int offset_to_next =
        static_cast<int>(*reinterpret_cast<int8_t*>(addr_at(fixup_pos)));
    ASSERT(offset_to_next <= 0);
    int disp = pos - (fixup_pos + sizeof(int8_t));
    ASSERT(is_int8(disp));
    set_byte_at(fixup_pos, disp);
    if (offset_to_next < 0) {
      L->link_to(fixup_pos + offset_to_next, Label::kNear);
    } else {
      L->UnuseNear();
    }
  }
  L->bind_to(pos);
}
