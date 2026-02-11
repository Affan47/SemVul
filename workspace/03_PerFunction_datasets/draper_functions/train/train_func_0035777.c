display_debug_str_offsets (struct dwarf_section *section,
                           void *file ATTRIBUTE_UNUSED)
{
  if (section->size == 0)
    {
      printf (_("\nThe %s section is empty.\n"), section->name);
      return 0;
    }


  return 1;
}
