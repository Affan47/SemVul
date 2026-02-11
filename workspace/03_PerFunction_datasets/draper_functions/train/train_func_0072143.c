coerce_indexer (NODE_T * p)
{
  if (p != NO_NODE) {
    if (IS (p, TRIMMER)) {
      coerce_trimmer (SUB (p));
    } else if (IS (p, UNIT)) {
      coerce_meek_int (p);
    } else {
      coerce_indexer (SUB (p));
      coerce_indexer (NEXT (p));
    }
  }
}
