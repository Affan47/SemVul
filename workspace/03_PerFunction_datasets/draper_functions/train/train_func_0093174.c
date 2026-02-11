visit_compilation_unit(off_t, off_t, Dwarf_die* die)
{
  this->dwo_id_ = die->uint_attribute(elfcpp::DW_AT_GNU_dwo_id);
  if (this->dwo_id_ != 0)
    this->dwo_id_found_ = true;
}
