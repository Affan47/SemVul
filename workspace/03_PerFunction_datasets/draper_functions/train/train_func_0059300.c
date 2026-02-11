lang_reset_memory_regions (void)
{
  lang_memory_region_type *p = lang_memory_region_list;
  asection *o;
  lang_output_section_statement_type *os;

  for (p = lang_memory_region_list; p != NULL; p = p->next)
    {
      p->current = p->origin;
      p->last_os = NULL;
    }

  for (os = &lang_output_section_statement.head->output_section_statement;
       os != NULL;
       os = os->next)
    {
      os->processed_vma = FALSE;
      os->processed_lma = FALSE;
    }

  for (o = link_info.output_bfd->sections; o != NULL; o = o->next)
    {

      o->rawsize = o->size;
      o->size = 0;
    }
}
