deps_has_edge (const reloc_deps_graph *deps,
	       lang_statement_union_type *src,
	       lang_statement_union_type *tgt)
{
  if (!section_is_source (deps, src))
    return FALSE;
  if (!section_is_target (deps, tgt))
    return FALSE;

  if (src->header.type != lang_input_section_enum)
    return FALSE;
  if (tgt->header.type != lang_input_section_enum)
    return FALSE;

  return deps_has_sec_edge (deps, src->input_section.section,
			    tgt->input_section.section);
}
