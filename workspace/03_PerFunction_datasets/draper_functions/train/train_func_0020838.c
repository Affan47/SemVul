get_qualified_name(Dwarf_die* die, Dwarf_die* context)
{
  std::string full_name;
  const char* name = die->name();

  off_t parent_offset = context != NULL ? context->offset() : 0;


  off_t spec = die->specification();
  if (spec == 0)
    spec = die->abstract_origin();
  if (spec > 0)
    {
      Declaration_map::iterator it = this->declarations_.find(spec);
      if (it != this->declarations_.end())
        {
	  parent_offset = it->second.parent_offset_;
	  name = it->second.name_;
        }
    }

  if (name == NULL && die->tag() == elfcpp::DW_TAG_namespace)
    name = "(anonymous namespace)";
  else if (name == NULL)
    return full_name;


  if (die->tag() == elfcpp::DW_TAG_enumerator)
    {
      Declaration_map::iterator it = this->declarations_.find(parent_offset);
      if (it != this->declarations_.end())
	parent_offset = it->second.parent_offset_;
    }

  if (parent_offset > 0)
    {
      full_name.assign(this->get_context(parent_offset));
      full_name.append("::");
    }
  full_name.append(name);

  return full_name;
}
