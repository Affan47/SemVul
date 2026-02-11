dump_ddrs (FILE *file, VEC (ddr_p, heap) *ddrs)
{
  unsigned int i;
  struct data_dependence_relation *ddr;

  FOR_EACH_VEC_ELT (ddr_p, ddrs, i, ddr)
    dump_data_dependence_relation (file, ddr);

  fprintf (file, "\n\n");
}
