tab_qualifier (NODE_T * p)
{
  if (p != NO_NODE) {
    if (is_one_of (p, UNIT, ASSIGNATION, TERTIARY, SECONDARY, GENERATOR, STOP)) {
      return (tab_qualifier (SUB (p)));
    } else if (is_one_of (p, LOC_SYMBOL, HEAP_SYMBOL, NEW_SYMBOL, STOP)) {
      return (ATTRIBUTE (p) == LOC_SYMBOL ? LOC_SYMBOL : HEAP_SYMBOL);
    } else {
      return (LOC_SYMBOL);
    }
  } else {
    return (LOC_SYMBOL);
  }
}
