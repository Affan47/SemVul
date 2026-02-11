bind_to(Label* L, int pos) {
  ASSERT(!L->is_bound());
  last_pc_ = NULL;
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
  L->bind_to(pos);
}
