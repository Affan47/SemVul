make_sub (NODE_T * p, NODE_T * q, int t)
{
  NODE_T *z = new_node ();
  ABEND (p == NO_NODE || q == NO_NODE, ERROR_INTERNAL_CONSISTENCY, "make_sub");
  *z = *p;
  if (GINFO (p) != NO_GINFO) {
    GINFO (z) = new_genie_info ();
  }
  PREVIOUS (z) = NO_NODE;
  if (p == q) {
    NEXT (z) = NO_NODE;
  } else {
    if (NEXT (p) != NO_NODE) {
      PREVIOUS (NEXT (p)) = z;
    }
    NEXT (p) = NEXT (q);
    if (NEXT (p) != NO_NODE) {
      PREVIOUS (NEXT (p)) = p;
    }
    NEXT (q) = NO_NODE;
  }
  SUB (p) = z;
  ATTRIBUTE (p) = t;
}
