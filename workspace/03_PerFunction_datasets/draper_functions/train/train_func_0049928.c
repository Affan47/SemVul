simple_object_elf_write_ehdr (simple_object_write *sobj, int descriptor,
			      const char **errmsg, int *err)
{
  struct simple_object_elf_attributes *attrs =
    (struct simple_object_elf_attributes *) sobj->data;
  const struct elf_type_functions* fns;
  unsigned char cl;
  size_t ehdr_size;
  unsigned char buf[sizeof (Elf64_External_Ehdr)];
  simple_object_write_section *section;
  unsigned int shnum;

  fns = attrs->type_functions;
  cl = attrs->ei_class;

  shnum = 0;
  for (section = sobj->sections; section != NULL; section = section->next)
    ++shnum;
  if (shnum > 0)
    {


      shnum += 2;
    }

  ehdr_size = (cl == ELFCLASS32
	       ? sizeof (Elf32_External_Ehdr)
	       : sizeof (Elf64_External_Ehdr));
  memset (buf, 0, sizeof (Elf64_External_Ehdr));

  buf[EI_MAG0] = ELFMAG0;
  buf[EI_MAG1] = ELFMAG1;
  buf[EI_MAG2] = ELFMAG2;
  buf[EI_MAG3] = ELFMAG3;
  buf[EI_CLASS] = cl;
  buf[EI_DATA] = attrs->ei_data;
  buf[EI_VERSION] = EV_CURRENT;
  buf[EI_OSABI] = attrs->ei_osabi;

  ELF_SET_FIELD (fns, cl, Ehdr, buf, e_type, Elf_Half, ET_REL);
  ELF_SET_FIELD (fns, cl, Ehdr, buf, e_machine, Elf_Half, attrs->machine);
  ELF_SET_FIELD (fns, cl, Ehdr, buf, e_version, Elf_Word, EV_CURRENT);


  ELF_SET_FIELD (fns, cl, Ehdr, buf, e_shoff, Elf_Addr, ehdr_size);
  ELF_SET_FIELD (fns, cl, Ehdr, buf, e_flags, Elf_Word, attrs->flags);
  ELF_SET_FIELD (fns, cl, Ehdr, buf, e_ehsize, Elf_Half, ehdr_size);
  ELF_SET_FIELD (fns, cl, Ehdr, buf, e_phentsize, Elf_Half,
		 (cl == ELFCLASS32
		  ? sizeof (Elf32_External_Phdr)
		  : sizeof (Elf64_External_Phdr)));

  ELF_SET_FIELD (fns, cl, Ehdr, buf, e_shentsize, Elf_Half,
		 (cl == ELFCLASS32
		  ? sizeof (Elf32_External_Shdr)
		  : sizeof (Elf64_External_Shdr)));
  ELF_SET_FIELD (fns, cl, Ehdr, buf, e_shnum, Elf_Half, shnum);
  ELF_SET_FIELD (fns, cl, Ehdr, buf, e_shstrndx, Elf_Half,
		 shnum == 0 ? 0 : shnum - 1);

  return simple_object_internal_write (descriptor, 0, buf, ehdr_size,
				       errmsg, err);
}
