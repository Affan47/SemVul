dump_ddrs (FILE *file, vec<ddr_p> ddrs)
{
  unsigned int i;
  struct data_dependence_relation *ddr;

  FOR_EACH_VEC_ELT (ddrs, i, ddr)
    dump_data_dependence_relation (file, ddr);

  fprintf (file, "\n\n");
}
