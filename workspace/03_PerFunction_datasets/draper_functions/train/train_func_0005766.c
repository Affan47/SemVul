add_output_section_data(const char* name, elfcpp::Elf_Word type,
				elfcpp::Elf_Xword flags,
				Output_section_data* posd,
				Output_section_order order, bool is_relro)
{
  Output_section* os = this->choose_output_section(NULL, name, type, flags,
						   false, order, is_relro);
  if (os != NULL)
    os->add_output_section_data(posd);
  return os;
}
