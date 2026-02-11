print_closure (char const *title, item_number const *array, size_t size)
{
  size_t i;
  fprintf (stderr, "Closure: %s\n", title);
  for (i = 0; i < size; ++i)
    {
      item_number *rp;
      fprintf (stderr, "  %2d: .", array[i]);
      for (rp = &ritem[array[i]]; *rp >= 0; ++rp)
        fprintf (stderr, " %s", symbols[*rp]->tag);
      fprintf (stderr, "  (rule %d)\n", -*rp - 1);
    }
  fputs ("\n\n", stderr);
}
