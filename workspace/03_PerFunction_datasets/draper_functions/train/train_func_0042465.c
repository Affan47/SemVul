record_cu_ranges(Dwarf_die* die)
{
  unsigned int shndx;
  unsigned int shndx2;

  off_t ranges_offset = die->ref_attribute(elfcpp::DW_AT_ranges, &shndx);
  if (ranges_offset != -1)
    {
      Dwarf_range_list* ranges = this->read_range_list(shndx, ranges_offset);
      if (ranges != NULL)
	this->gdb_index_->add_address_range_list(this->object(),
						 this->cu_index_, ranges);
      return;
    }

  off_t low_pc = die->address_attribute(elfcpp::DW_AT_low_pc, &shndx);
  off_t high_pc = die->address_attribute(elfcpp::DW_AT_high_pc, &shndx2);
  if (high_pc == -1)
    {
      high_pc = die->uint_attribute(elfcpp::DW_AT_high_pc);
      high_pc += low_pc;
      shndx2 = shndx;
    }
  if ((low_pc != 0 || high_pc != 0) && low_pc != -1)
    {
      if (shndx != shndx2)
        {
	  gold_warning(_("%s: DWARF info may be corrupt; low_pc and high_pc "
			 "are in different sections"),
		       this->object()->name().c_str());
	  return;
	}
      if (shndx == 0 || this->object()->is_section_included(shndx))
        {
	  Dwarf_range_list* ranges = new Dwarf_range_list();
	  ranges->add(shndx, low_pc, high_pc);
	  this->gdb_index_->add_address_range_list(this->object(),
						   this->cu_index_, ranges);
        }
    }
}
