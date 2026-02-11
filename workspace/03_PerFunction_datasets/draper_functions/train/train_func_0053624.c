set_final_data_size()
{

  this->stringpool_.set_string_offsets();


  unsigned int cu_vector_count = this->cu_vector_list_.size();
  unsigned int cu_vector_size = 0;
  this->cu_vector_offsets_ = new off_t[cu_vector_count];
  for (unsigned int i = 0; i < cu_vector_count; ++i)
    {
      Cu_vector* cu_vec = this->cu_vector_list_[i];
      cu_vector_offsets_[i] = cu_vector_size;
      cu_vector_size += gdb_index_offset_size * (cu_vec->size() + 1);
    }


  section_size_type data_size = gdb_index_hdr_size;
  data_size += this->comp_units_.size() * gdb_index_cu_size;
  this->tu_offset_ = data_size;
  data_size += this->type_units_.size() * gdb_index_tu_size;
  this->addr_offset_ = data_size;
  for (unsigned int i = 0; i < this->ranges_.size(); ++i)
    data_size += this->ranges_[i].ranges->size() * gdb_index_addr_size;
  this->symtab_offset_ = data_size;
  data_size += this->gdb_symtab_->capacity() * gdb_index_sym_size;
  this->cu_pool_offset_ = data_size;
  data_size += cu_vector_size;
  this->stringpool_offset_ = data_size;
  data_size += this->stringpool_.get_strtab_size();

  this->set_data_size(data_size);
}
