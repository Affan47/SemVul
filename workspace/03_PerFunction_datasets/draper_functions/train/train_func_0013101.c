strip_all(void)
{
  gp_section_type *section = state.object->sections;

  if (state.object->flags & F_EXEC) {
    while (section != NULL) {


      section->num_lineno = 0;
      section->line_numbers = NULL;
      section->line_numbers_tail = NULL;


      section->num_reloc = 0;
      section->relocations = NULL;
      section->relocations_tail = NULL;

      section = section->next;
    }


    state.object->num_symbols = 0;
    state.object->symbols = NULL;
    state.object->symbols_tail = NULL;

  } else {
    gp_error("can not strip all symbols because the object file is not executable");
  }

}
