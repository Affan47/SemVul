should_apply_static_reloc(const Sized_symbol<32>* gsym,
						 unsigned int r_type,
						 bool is_32bit,
						 Output_section* output_section)
{


  if ((output_section->flags() & elfcpp::SHF_ALLOC) == 0)
    return true;

  int ref_flags = Scan::get_reference_flags(r_type);


  if (gsym == NULL)
    return !(parameters->options().output_is_position_independent()
	     && (ref_flags & Symbol::ABSOLUTE_REF)
	     && !is_32bit);


  bool has_dyn = gsym->needs_dynamic_reloc(ref_flags);
  bool is_rel = (ref_flags & Symbol::ABSOLUTE_REF)
		&& gsym->can_use_relative_reloc(ref_flags
						& Symbol::FUNCTION_CALL);
  return !has_dyn || is_rel;
}
