tax_routine_texts (NODE_T * p)
{
  for (; p != NO_NODE; FORWARD (p)) {
    tax_routine_texts (SUB (p));
    if (IS (p, ROUTINE_TEXT)) {
      TAG_T *z = add_tag (TABLE (p), ANONYMOUS, p, MOID (p), ROUTINE_TEXT);
      TAX (p) = z;
      HEAP (z) = LOC_SYMBOL;
      USE (z) = A68_TRUE;
    }
  }
}
