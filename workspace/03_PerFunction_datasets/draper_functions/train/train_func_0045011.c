fprint_estack_mem(FILE *fp, int heading)
{
  int n;
  if (heading)
    fprintf(fp, "  type (bytes each)        gets      frees     in use      bytes\n");

  n = sizeof(struct estack);

  fprintf(fp, "estack (%4d)       %11u%11u%11u%9.1f K (avail=%u, %.1f K)\n",
          n, Estack_gets, Estack_frees,
          Estack_gets - Estack_frees,
          ((Estack_gets - Estack_frees) * n) / 1024.,
	  Estack_avails,
	  (Estack_avails * n) / 1024.);


}
