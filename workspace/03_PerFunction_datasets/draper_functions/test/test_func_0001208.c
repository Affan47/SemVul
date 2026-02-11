process_mips_fpe_exception (int mask)
{
  if (mask)
    {
      int first = 1;
      if (mask & OEX_FPU_INEX)
	fputs ("INEX", stdout), first = 0;
      if (mask & OEX_FPU_UFLO)
	printf ("%sUFLO", first ? "" : "|"), first = 0;
      if (mask & OEX_FPU_OFLO)
	printf ("%sOFLO", first ? "" : "|"), first = 0;
      if (mask & OEX_FPU_DIV0)
	printf ("%sDIV0", first ? "" : "|"), first = 0;
      if (mask & OEX_FPU_INVAL)
	printf ("%sINVAL", first ? "" : "|");
    }
  else
    fputs ("0", stdout);
}
