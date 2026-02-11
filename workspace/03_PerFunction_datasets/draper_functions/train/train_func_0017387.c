dump_ds (FILE *f, ds_t s)
{
  fprintf (f, "{");

  if (s & BEGIN_DATA)
    fprintf (f, "BEGIN_DATA: %d; ", get_dep_weak_1 (s, BEGIN_DATA));
  if (s & BE_IN_DATA)
    fprintf (f, "BE_IN_DATA: %d; ", get_dep_weak_1 (s, BE_IN_DATA));
  if (s & BEGIN_CONTROL)
    fprintf (f, "BEGIN_CONTROL: %d; ", get_dep_weak_1 (s, BEGIN_CONTROL));
  if (s & BE_IN_CONTROL)
    fprintf (f, "BE_IN_CONTROL: %d; ", get_dep_weak_1 (s, BE_IN_CONTROL));

  if (s & HARD_DEP)
    fprintf (f, "HARD_DEP; ");

  if (s & DEP_TRUE)
    fprintf (f, "DEP_TRUE; ");
  if (s & DEP_OUTPUT)
    fprintf (f, "DEP_OUTPUT; ");
  if (s & DEP_ANTI)
    fprintf (f, "DEP_ANTI; ");
  if (s & DEP_CONTROL)
    fprintf (f, "DEP_CONTROL; ");

  fprintf (f, "}");
}
