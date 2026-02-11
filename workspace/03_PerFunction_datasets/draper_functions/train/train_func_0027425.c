resolve_unique_section (tree decl, int reloc ATTRIBUTE_UNUSED,
			int flag_function_or_data_sections)
{
  if (DECL_SECTION_NAME (decl) == NULL_TREE
      && targetm.have_named_sections
      && (flag_function_or_data_sections
	  || DECL_ONE_ONLY (decl)))
    {
      targetm.asm_out.unique_section (decl, reloc);
      DECL_HAS_IMPLICIT_SECTION_NAME_P (decl) = true;
    }
}
