get_symbol_table_index (tree t, tree special,
			vec<method_entry, va_gc> **symbol_table)
{
  method_entry *e;
  unsigned i;
  method_entry elem = {t, special};

  FOR_EACH_VEC_SAFE_ELT (*symbol_table, i, e)
    if (t == e->method && special == e->special)
      goto done;

  vec_safe_push (*symbol_table, elem);

 done:
  return i + 1;
}
