do_finalize_sections(
    Layout* layout,
    const Input_objects*,
    Symbol_table* symtab)
{
  const Reloc_section* rel_plt = (this->plt_ == NULL
				  ? NULL
				  : this->plt_->rel_plt());
  layout->add_target_dynamic_tags(true, this->got_plt_, rel_plt,
				  this->rel_dyn_, true, false);


  if (this->copy_relocs_.any_saved_relocs())
    this->copy_relocs_.emit(this->rel_dyn_section(layout));


  Symbol* sym = this->global_offset_table_;
  if (sym != NULL)
    {
      uint32_t data_size = this->got_plt_->current_data_size();
      symtab->get_sized_symbol<32>(sym)->set_symsize(data_size);
    }

  if (parameters->doing_static_link()
      && (this->plt_ == NULL || !this->plt_->has_irelative_section()))
    {


      static const Define_symbol_in_segment syms[] =
	{
	  {
	    "__rel_iplt_start",
	    elfcpp::PT_LOAD,
	    elfcpp::PF_W,
	    elfcpp::PF(0),
	    0,
	    0,
	    elfcpp::STT_NOTYPE,
	    elfcpp::STB_GLOBAL,
	    elfcpp::STV_HIDDEN,
	    0,
	    Symbol::SEGMENT_START,
	    true
	  },
	  {
	    "__rel_iplt_end",
	    elfcpp::PT_LOAD,
	    elfcpp::PF_W,
	    elfcpp::PF(0),
	    0,
	    0,
	    elfcpp::STT_NOTYPE,
	    elfcpp::STB_GLOBAL,
	    elfcpp::STV_HIDDEN,
	    0,
	    Symbol::SEGMENT_START,
	    true
	  }
	};

      symtab->define_symbols(layout, 2, syms,
			     layout->script_options()->saw_sections_clause());
    }
}
