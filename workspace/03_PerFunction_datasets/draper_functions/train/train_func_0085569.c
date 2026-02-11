process_object (const char *file_name, FILE *file)
{

  long offset = ftell (file);

  if (! get_file_header (file))
    {
      error (_("%s: Failed to read ELF header\n"), file_name);
      return 1;
    }


  if (fseek (file, offset, SEEK_SET) != 0)
    {
      error (_("%s: Failed to seek to ELF header\n"), file_name);
    }

  if (! update_elf_header (file_name, file))
    return 1;

  return 0;
}
