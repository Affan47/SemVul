fprint_just_mem(FILE *fp, BOOL heading)
{
  int n;
  if (heading)
    fprintf(fp, "  type (bytes each)        gets      frees     in use      bytes\n");

  n = sizeof(struct just);
  fprintf(fp, "just (%4d)         %11u%11u%11u%9.1f K\n",
          n, Just_gets, Just_frees,
          Just_gets - Just_frees,
          ((Just_gets - Just_frees) * n) / 1024.);

  n = sizeof(struct parajust);
  fprintf(fp, "parajust (%4d)     %11u%11u%11u%9.1f K\n",
          n, Parajust_gets, Parajust_frees,
          Parajust_gets - Parajust_frees,
          ((Parajust_gets - Parajust_frees) * n) / 1024.);

  n = sizeof(struct instancejust);
  fprintf(fp, "instancejust (%4d) %11u%11u%11u%9.1f K\n",
          n, Instancejust_gets, Instancejust_frees,
          Instancejust_gets - Instancejust_frees,
          ((Instancejust_gets - Instancejust_frees) * n) / 1024.);

  n = sizeof(struct ivyjust);
  fprintf(fp, "ivyjust (%4d)      %11u%11u%11u%9.1f K\n",
          n, Ivyjust_gets, Ivyjust_frees,
          Ivyjust_gets - Ivyjust_frees,
          ((Ivyjust_gets - Ivyjust_frees) * n) / 1024.);

}
