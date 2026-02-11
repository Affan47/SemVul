symbol_bd_sql_get_symbols_matches (Symbolizable *self, const gchar *symbol_prefix, gint flags)
{
  gphpedit_debug (DEBUG_SYMBOLIZABLE);
  SymbolBdSQLDetails *symbolbddet;
  symbolbddet = SYMBOL_BD_SQL_GET_PRIVATE(self);
  symbolbddet->completion_prefix = (gchar *) symbol_prefix;
  symbolbddet->completion_string = NULL;

  if (symbol_bd_sql_has_cache(symbolbddet->cache_str, symbolbddet->cache_completion, symbolbddet->cache_flags, symbol_prefix, flags)){
    symbolbddet->completion_string = symbol_bd_get_autocomp_from_cache(symbolbddet->cache_str, symbolbddet->cache_completion, symbol_prefix);
  } else {
    symbolbddet->completion_tree = g_tree_new_full ((GCompareDataFunc) g_strcmp0, NULL, NULL,(GDestroyNotify) g_free);

    if (((flags & SYMBOL_ALL) == SYMBOL_ALL) || ((flags & SYMBOL_FUNCTION) == SYMBOL_FUNCTION)) {

      g_tree_foreach (symbolbddet->sql_api_tree, add_api_item, symbolbddet);
    }
    g_tree_foreach (symbolbddet->completion_tree, make_result_string, symbolbddet);
    g_tree_destroy (symbolbddet->completion_tree);
    if (symbolbddet->completion_string) symbol_bd_sql_save_result_in_cache(symbolbddet, symbolbddet->completion_string->str, symbol_prefix);
  }

  if (symbolbddet->completion_string){
    gphpedit_debug_message(DEBUG_CLASSBROWSER, "prefix: %s autocomplete list:%s\n", symbol_prefix, symbolbddet->completion_string->str);
    return g_string_free(symbolbddet->completion_string, FALSE);
  }

  gphpedit_debug_message(DEBUG_CLASSBROWSER, "prefix: %s autocomplete list:%s\n", symbol_prefix, "null");
  return NULL;
}
