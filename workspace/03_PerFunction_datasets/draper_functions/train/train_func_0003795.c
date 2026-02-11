toDtI (dt_t **pdt, int off)
{
  tree dt = build_address (toSymbol()->Stree);

  if (off != 0)
    dt = build_offset (dt, size_int (off));

  return dt_cons (pdt, dt);
}
