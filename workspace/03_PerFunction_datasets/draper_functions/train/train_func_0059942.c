map_pubnames_and_types_to_dies(Gdb_index_info_reader* dwinfo,
                                          Relobj* object,
                                          const unsigned char* symbols,
                                          off_t symbols_size)
{

  this->pubnames_object_ = object;
  this->stmt_list_offset_ = -1;

  delete this->pubnames_table_;
  this->pubnames_table_
      = this->map_pubtable_to_dies(elfcpp::DW_AT_GNU_pubnames, dwinfo,
                                   object, symbols, symbols_size);
  delete this->pubtypes_table_;
  this->pubtypes_table_
      = this->map_pubtable_to_dies(elfcpp::DW_AT_GNU_pubtypes, dwinfo,
                                   object, symbols, symbols_size);
}
