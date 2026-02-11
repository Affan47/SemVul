tax_op_dec (NODE_T * p, MOID_T ** m)
{
  if (p != NO_NODE) {
    if (IS (p, OPERATOR_DECLARATION)) {
      tax_op_dec (SUB (p), m);
      tax_op_dec (NEXT (p), m);
    } else if (IS (p, OPERATOR_PLAN)) {
      tax_tags (SUB (p));
      *m = MOID (p);
      tax_op_dec (NEXT (p), m);
    } else if (IS (p, OP_SYMBOL)) {
      tax_op_dec (NEXT (p), m);
    } else if (IS (p, COMMA_SYMBOL)) {
      tax_op_dec (NEXT (p), m);
    } else if (IS (p, DEFINING_OPERATOR)) {
      TAG_T *entry = OPERATORS (TABLE (p));
      check_operator_dec (p);
      while (entry != NO_TAG && NODE (entry) != p) {
        FORWARD (entry);
      }
      MOID (p) = *m;
      TAX (p) = entry;
      HEAP (entry) = LOC_SYMBOL;
      MOID (entry) = *m;
      tax_op_dec (NEXT (p), m);
    } else {
      tax_tags (p);
    }
  }
}
