usage(const char *prog)
{
  size_t i;
  fprintf(stderr, "Usage: %s [", prog ? prog : "uu_decode");
  for (i=0; i<NELEM(options); ++i)
    {
      fprintf(stderr, "%s %s", (i>0) ? " |" : "", options[i]);
    }
  fprintf(stderr, " ]\n");
}
