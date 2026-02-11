init_assoc (void)
{
  graphid i;
  used_assoc = xcalloc (nsyms, sizeof *used_assoc);
  for (i = 0; i < nsyms; ++i)
    used_assoc[i] = false;
}
