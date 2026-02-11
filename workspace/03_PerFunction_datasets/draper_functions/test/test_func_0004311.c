aarch64_elf_asm_named_section (const char *name, unsigned int flags,
			       tree decl ATTRIBUTE_UNUSED)
{
  char flagchars[10], *f = flagchars;


  if (!(HAVE_COMDAT_GROUP && (flags & SECTION_LINKONCE))
      && (flags & SECTION_DECLARED))
    {
      fprintf (asm_out_file, "\t.section\t%s\n", name);
      return;
    }

  if (!(flags & SECTION_DEBUG))
    *f++ = 'a';
  if (flags & SECTION_WRITE)
    *f++ = 'w';
  if (flags & SECTION_CODE)
    *f++ = 'x';
  if (flags & SECTION_SMALL)
    *f++ = 's';
  if (flags & SECTION_MERGE)
    *f++ = 'M';
  if (flags & SECTION_STRINGS)
    *f++ = 'S';
  if (flags & SECTION_TLS)
    *f++ = TLS_SECTION_ASM_FLAG;
  if (HAVE_COMDAT_GROUP && (flags & SECTION_LINKONCE))
    *f++ = 'G';
  *f = '\0';

  fprintf (asm_out_file, "\t.section\t%s,\"%s\"", name, flagchars);

  if (!(flags & SECTION_NOTYPE))
    {
      const char *type;
      const char *format;

      if (flags & SECTION_BSS)
	type = "nobits";
      else
	type = "progbits";

#ifdef TYPE_OPERAND_FMT
      format = "," TYPE_OPERAND_FMT;
#else
      format = ",@%s";
#endif

      fprintf (asm_out_file, format, type);

      if (flags & SECTION_ENTSIZE)
	fprintf (asm_out_file, ",%d", flags & SECTION_ENTSIZE);
      if (HAVE_COMDAT_GROUP && (flags & SECTION_LINKONCE))
	{
	  if (TREE_CODE (decl) == IDENTIFIER_NODE)
	    fprintf (asm_out_file, ",%s,comdat", IDENTIFIER_POINTER (decl));
	  else
	    fprintf (asm_out_file, ",%s,comdat",
		     IDENTIFIER_POINTER (DECL_COMDAT_GROUP (decl)));
	}
    }

  putc ('\n', asm_out_file);
}
