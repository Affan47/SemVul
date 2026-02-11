demangle_new_symbols (void)
{
  symbol *sym;

  while ((sym = symbol_pop ()) != NULL)
    {
      demangled *dem;
      const char *p = cplus_demangle (sym->key, DMGL_PARAMS | DMGL_ANSI);

      if (! p)
	continue;

      dem = demangled_hash_lookup (p, true);
      VEC_safe_push (str, heap, dem->mangled, sym->key);
    }
}
