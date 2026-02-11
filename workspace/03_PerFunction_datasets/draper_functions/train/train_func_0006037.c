read_then_get_elf(char *Str)
{
  FILE *elffile;
  char *infile="";

  verbosemode=1;
  if (1)
  {
  infile=Str;
  if ((elffile=fopen(infile, "rb")))
  {
    fseek(elffile, 0, SEEK_END);
    elfsize=ftell(elffile);
    fseek(elffile, 0, SEEK_SET);

    if ((elfbuffer=malloc(elfsize)))
    {
      fread(elfbuffer, elfsize, 1, elffile);
      elfheader=(struct Elf32_Ehdr *) elfbuffer;

      if (verbosemode==1) printf("ELF Loader v0.1a:\n");
      printf("ELF file size: %ld bytes.\n", elfsize);

      if (elfheader->e_ident[EI_MAG0]==0x7F &&
          elfheader->e_ident[EI_MAG1]=='E' &&
          elfheader->e_ident[EI_MAG2]=='L' &&
          elfheader->e_ident[EI_MAG3]=='F' &&
          elfheader->e_ident[EI_CLASS]==1 &&
          elfheader->e_ident[EI_DATA]==2 &&
          elfheader->e_ident[EI_VERSION]==EV_CURRENT &&
          ECW(elfheader->e_machine)==EM_68K &&
          ECL(elfheader->e_version)==EV_CURRENT)

      {
        printf("Identified as Motorola 68k 32Bit ELF file, version: %ld.\n",ECL(elfheader->e_version));

        if ((ECW(elfheader->e_type)==ET_REL) || (ECW(elfheader->e_type)==ET_EXEC))
        {
          if (ECW(elfheader->e_shentsize)==sizeof(struct Elf32_Shdr))
          {
            ULONG mainadr;
            printf("Section size is Ok. There are %d sections.\n", ECW(elfheader->e_shnum));
            elfsections=(struct Elf32_Shdr *) (elfbuffer+ECL(elfheader->e_shoff));

            scan_sections();
            if ((progbuffer=malloc(proglength)))
            {
              printf("Using base address $%lx.\n", baseaddress);

              load_program();

              mainadr=get_sym_addr("main")+baseaddress;
              free(progbuffer);
            }
            else printf("Error: not enough memory!\n");
          }
        }
      }

      free(elfbuffer);
    }
    else printf("Error: not enough memory!\n");

    fclose(elffile);
  }
}
  return 0;
}
