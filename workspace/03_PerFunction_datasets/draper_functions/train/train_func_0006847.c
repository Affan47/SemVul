add_symbol(int cu_index, const char* sym_name)
{
  unsigned int hash = mapped_index_string_hash(
      reinterpret_cast<const unsigned char*>(sym_name));
  Gdb_symbol* sym = new Gdb_symbol();
  this->stringpool_.add(sym_name, true, &sym->name_key);
  sym->hashval = hash;
  sym->cu_vector_index = 0;

  Gdb_symbol* found = this->gdb_symtab_->add(sym);
  if (found == sym)
    {

      found->cu_vector_index = this->cu_vector_list_.size();
      this->cu_vector_list_.push_back(new Cu_vector());
    }
  else
    {


      delete sym;
    }


  Cu_vector* cu_vec = this->cu_vector_list_[found->cu_vector_index];
  if (cu_vec->size() == 0 || cu_vec->back() != cu_index)
    cu_vec->push_back(cu_index);
}
