dump_component (FILE *file, struct component *comp)
{
  dref a;
  unsigned i;

  fprintf (file, "Component%s:\n",
	   comp->comp_step == RS_INVARIANT ? " (invariant)" : "");
  FOR_EACH_VEC_ELT (dref, comp->refs, i, a)
    dump_dref (file, a);
  fprintf (file, "\n");
}
