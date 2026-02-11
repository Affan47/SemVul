ambiguous_patterns (NODE_T * p)
{


  NODE_T *q, *last_pat = NO_NODE;
  for (q = p; q != NO_NODE; FORWARD (q)) {
    switch (ATTRIBUTE (q)) {
    case INTEGRAL_PATTERN:
    case REAL_PATTERN:
    case COMPLEX_PATTERN:
    case BITS_PATTERN:
      {
        if (last_pat != NO_NODE) {
          diagnostic_node (A68_SYNTAX_ERROR, q, ERROR_COMMA_MUST_SEPARATE, ATTRIBUTE (last_pat), ATTRIBUTE (q));
        }
        last_pat = q;
        break;
      }
    case COMMA_SYMBOL:
      {
        last_pat = NO_NODE;
        break;
      }
    }
  }
}
