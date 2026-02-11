SymbolMapForString(String* string) {

  if (InNewSpace(string)) return NULL;


  Map* map = string->map();
  if (map == ascii_string_map()) return ascii_symbol_map();
  if (map == string_map()) return symbol_map();
  if (map == cons_string_map()) return cons_symbol_map();
  if (map == cons_ascii_string_map()) return cons_ascii_symbol_map();
  if (map == external_string_map()) return external_symbol_map();
  if (map == external_ascii_string_map()) return external_ascii_symbol_map();
  if (map == external_string_with_ascii_data_map()) {
    return external_symbol_with_ascii_data_map();
  }


  return NULL;
}
