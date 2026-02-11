advance_ref(FILE *fref, struct acgtn *pacgtn)
{
  if (feof(fref))
    return 0;
  while (1)
  {
    int result = fgetc(fref);

    if (result == EOF)
    {
      if (feof(fref))
      {
        return 0;
      } else {
        perror("read");
        return -1;
      }
    }

    pacgtn->nt = result;

    if (pacgtn->nt == '\n')
      continue;

    pacgtn->index = nt_to_acgtn_index_silent(pacgtn->nt);
    if (pacgtn->index < 0)
    {
      fprintf(stderr, "invalid nucleotide in the sequence file: %c\n",
          pacgtn->nt);
      return -1;
    }

    return 1;
  }
}
