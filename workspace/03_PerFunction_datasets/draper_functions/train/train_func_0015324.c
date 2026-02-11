dump_mem_ref (FILE *file, struct mem_ref *ref)
{
  fprintf (file, "Reference %p:\n", (void *) ref);

  fprintf (file, "  group %p (base ", (void *) ref->group);
  print_generic_expr (file, ref->group->base, TDF_SLIM);
  fprintf (file, ", step ");
  if (cst_and_fits_in_hwi (ref->group->step))
    fprintf (file, HOST_WIDE_INT_PRINT_DEC, int_cst_value (ref->group->step));
  else
    print_generic_expr (file, ref->group->step, TDF_TREE);
  fprintf (file, ")\n");

  fprintf (file, "  delta ");
  fprintf (file, HOST_WIDE_INT_PRINT_DEC, ref->delta);
  fprintf (file, "\n");

  fprintf (file, "  %s\n", ref->write_p ? "write" : "read");

  fprintf (file, "\n");
}
