mips_symbol (str)

char *str;
  {
  char *seg;

  if (MPS_ADRSPC == 'T')
    seg = "text";
  else
    seg = "data";

  fprintf (MPS_SYMFIL, "%s\t: location %x in %s segment\n", str,
           MPS_ADDRES, seg);
  }
