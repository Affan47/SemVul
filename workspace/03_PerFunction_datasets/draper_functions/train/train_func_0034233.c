operator()(const Input_section_info& isi1,
				 const Input_section_info& isi2) const
{
  if (this->section_sort_ == SORT_WILDCARD_BY_NAME
      || this->section_sort_ == SORT_WILDCARD_BY_NAME_BY_ALIGNMENT
      || (this->section_sort_ == SORT_WILDCARD_BY_ALIGNMENT_BY_NAME
	  && isi1.addralign() == isi2.addralign()))
    {
      if (isi1.section_name() != isi2.section_name())
	return isi1.section_name() < isi2.section_name();
    }
  if (this->section_sort_ == SORT_WILDCARD_BY_ALIGNMENT
      || this->section_sort_ == SORT_WILDCARD_BY_NAME_BY_ALIGNMENT
      || this->section_sort_ == SORT_WILDCARD_BY_ALIGNMENT_BY_NAME)
    {
      if (isi1.addralign() != isi2.addralign())
	return isi1.addralign() < isi2.addralign();
    }
  if (this->filename_sort_ == SORT_WILDCARD_BY_NAME)
    {
      if (isi1.relobj()->name() != isi2.relobj()->name())
	return (isi1.relobj()->name() < isi2.relobj()->name());
    }


  return false;
}
