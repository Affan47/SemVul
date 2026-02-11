display_sparc_hwcaps (int mask)
{
  if (mask)
    {
      int first = 1;
      if (mask & ELF_SPARC_HWCAP_MUL32)
	fputs ("mul32", stdout), first = 0;
      if (mask & ELF_SPARC_HWCAP_DIV32)
	printf ("%sdiv32", first ? "" : "|"), first = 0;
      if (mask & ELF_SPARC_HWCAP_FSMULD)
	printf ("%sfsmuld", first ? "" : "|"), first = 0;
      if (mask & ELF_SPARC_HWCAP_V8PLUS)
	printf ("%sv8plus", first ? "" : "|"), first = 0;
      if (mask & ELF_SPARC_HWCAP_POPC)
	printf ("%spopc", first ? "" : "|"), first = 0;
      if (mask & ELF_SPARC_HWCAP_VIS)
	printf ("%svis", first ? "" : "|"), first = 0;
      if (mask & ELF_SPARC_HWCAP_VIS2)
	printf ("%svis2", first ? "" : "|"), first = 0;
      if (mask & ELF_SPARC_HWCAP_ASI_BLK_INIT)
	printf ("%sASIBlkInit", first ? "" : "|"), first = 0;
      if (mask & ELF_SPARC_HWCAP_FMAF)
	printf ("%sfmaf", first ? "" : "|"), first = 0;
      if (mask & ELF_SPARC_HWCAP_VIS3)
	printf ("%svis3", first ? "" : "|"), first = 0;
      if (mask & ELF_SPARC_HWCAP_HPC)
	printf ("%shpc", first ? "" : "|"), first = 0;
      if (mask & ELF_SPARC_HWCAP_RANDOM)
	printf ("%srandom", first ? "" : "|"), first = 0;
      if (mask & ELF_SPARC_HWCAP_TRANS)
	printf ("%strans", first ? "" : "|"), first = 0;
      if (mask & ELF_SPARC_HWCAP_FJFMAU)
	printf ("%sfjfmau", first ? "" : "|"), first = 0;
      if (mask & ELF_SPARC_HWCAP_IMA)
	printf ("%sima", first ? "" : "|"), first = 0;
      if (mask & ELF_SPARC_HWCAP_ASI_CACHE_SPARING)
	printf ("%scspare", first ? "" : "|"), first = 0;
    }
  else
    fputc('0', stdout);
  fputc('\n', stdout);
}
