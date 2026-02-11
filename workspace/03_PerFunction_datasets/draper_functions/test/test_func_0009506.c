elf_find_dynamic_section(int fd, Elf_Ehdr *ehdr, Elf_Phdr *phdr)
{
  int i;
  if (lseek(fd, EHDR_PWU(e_phoff), SEEK_SET) == -1)
  {
    perror ("positioning for sections");
    return 1;
  }

  for (i = 0; i < EHDR_PHS(e_phnum); i++)
  {
    const size_t sz_phdr = is_e32() ? sizeof(Elf32_Phdr) : sizeof(Elf64_Phdr);
    if (read(fd, phdr, sz_phdr) != (ssize_t)sz_phdr)
    {
      perror ("reading section header");
      return 1;
    }
    if (PHDR_PWU(p_type) == PT_DYNAMIC)
      break;
  }
  if (i == EHDR_PHS(e_phnum))
    {
      fprintf (stderr, "No dynamic section found.\n");
      return 2;
    }

  if (0 == PHDR_POU(p_filesz))
    {
      fprintf (stderr, "Length of dynamic section is zero.\n");
      return 3;
    }

  return 0;
}
