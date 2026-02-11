eval_load_address(Symbol_table* symtab, Layout* layout)
  {
    if (this->load_address_ != NULL)
      this->load_address_value_ = this->load_address_->eval(symtab, layout,
							    true);
  }
