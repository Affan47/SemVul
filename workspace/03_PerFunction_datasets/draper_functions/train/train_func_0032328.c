do_make_output_section(const char* name, elfcpp::Elf_Word type,
			       elfcpp::Elf_Xword flags)
{
  return new Output_section(name, type, flags);
}
