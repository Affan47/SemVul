obj_elf_popsection (int xxx ATTRIBUTE_UNUSED)
{
  struct section_stack *top = section_stack;

  if (top == NULL)
    {
      as_warn (_(".popsection without corresponding .pushsection; ignored"));
      return;
    }

#ifdef md_flush_pending_output
  md_flush_pending_output ();
#endif

  section_stack = top->next;
  previous_section = top->prev_seg;
  previous_subsection = top->prev_subseg;
  subseg_set (top->seg, top->subseg);
  free (top);

#ifdef md_elf_section_change_hook
  md_elf_section_change_hook ();
#endif
}
