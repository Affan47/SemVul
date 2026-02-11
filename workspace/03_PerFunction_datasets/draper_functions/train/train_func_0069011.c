file_end_indicate_exec_stack (void)
{
  unsigned int flags = SECTION_DEBUG;
  if (trampolines_created)
    flags |= SECTION_CODE;

  named_section_flags (".note.GNU-stack", flags);
}
