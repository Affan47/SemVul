kfold_int64arith(uint64_t k1, uint64_t k2, IROp op)
{
  switch (op) {
#if LJ_64 || LJ_HASFFI
  case IR_ADD: k1 += k2; break;
  case IR_SUB: k1 -= k2; break;
#endif
#if LJ_HASFFI
  case IR_MUL: k1 *= k2; break;
  case IR_BAND: k1 &= k2; break;
  case IR_BOR: k1 |= k2; break;
  case IR_BXOR: k1 ^= k2; break;
#endif
  default: UNUSED(k2); lua_assert(0); break;
  }
  return k1;
}
