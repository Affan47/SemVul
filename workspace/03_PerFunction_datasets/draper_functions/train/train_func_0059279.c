dump_ia64_vms_dynamic_relocs (FILE *file, struct ia64_vms_dynimgrela *imgrela)
{
  Elf64_External_VMS_IMAGE_RELA *imrs;
  long i;

  imrs = get_data (NULL, file, dynamic_addr + imgrela->img_rela_off,
		   1, imgrela->img_rela_cnt * sizeof (*imrs),
		   _("dynamic section image relocations"));
  if (!imrs)
    return;

  printf (_("\nImage relocs\n"));
  printf
    (_("Seg Offset   Type                            Addend            Seg Sym Off\n"));

  for (i = 0; i < (long) imgrela->img_rela_cnt; i++)
    {
      unsigned int type;
      const char *rtype;

      printf ("%3u ", (unsigned) BYTE_GET (imrs [i].rela_seg));
      printf ("%08" BFD_VMA_FMT "x ",
              (bfd_vma) BYTE_GET (imrs [i].rela_offset));
      type = BYTE_GET (imrs [i].type);
      rtype = elf_ia64_reloc_type (type);
      if (rtype == NULL)
        printf ("0x%08x                      ", type);
      else
        printf ("%-31s ", rtype);
      print_vma (BYTE_GET (imrs [i].addend), FULL_HEX);
      printf ("%3u ", (unsigned) BYTE_GET (imrs [i].sym_seg));
      printf ("%08" BFD_VMA_FMT "x\n",
              (bfd_vma) BYTE_GET (imrs [i].sym_offset));
    }

  free (imrs);
}
