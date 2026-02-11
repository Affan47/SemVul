string_to_object_format(const char* arg)
{
  if (strncmp(arg, "elf", 3) == 0 || strcmp(arg, "default") == 0)
    return gold::General_options::OBJECT_FORMAT_ELF;
  else if (strcmp(arg, "binary") == 0)
    return gold::General_options::OBJECT_FORMAT_BINARY;
  else
    {
      gold::gold_error(_("format '%s' not supported; treating as elf "
			 "(supported formats: elf, binary)"),
		       arg);
      return gold::General_options::OBJECT_FORMAT_ELF;
    }
}
