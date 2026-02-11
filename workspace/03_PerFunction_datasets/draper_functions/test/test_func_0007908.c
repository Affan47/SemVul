print_memory_map_header()
{
  if (!this->printed_memory_map_header_)
    {
      fprintf(this->map_file_, _("\nMemory map\n\n"));
      this->printed_memory_map_header_ = true;
    }
}
