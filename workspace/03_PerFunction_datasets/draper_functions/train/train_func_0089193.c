is_loop_cast_formula (NODE_T * p)
{

  if (IS (p, VOID_SYMBOL)) {
    return (1);
  } else if (IS (p, INT_SYMBOL)) {
    return (1);
  } else if (IS (p, REF_SYMBOL)) {
    return (1);
  } else if (is_one_of (p, OPERATOR, BOLD_TAG, STOP)) {
    return (1);
  } else if (whether (p, UNION_SYMBOL, OPEN_SYMBOL, STOP)) {
    return (2);
  } else if (is_one_of (p, OPEN_SYMBOL, SUB_SYMBOL, STOP)) {
    int k;
    for (k = 0; p != NO_NODE && (is_one_of (p, OPEN_SYMBOL, SUB_SYMBOL, STOP)); FORWARD (p), k++) {
      ;
    }
    return (p != NO_NODE && (whether (p, UNION_SYMBOL, OPEN_SYMBOL, STOP) ? k : 0));
  }
  return (0);
}
