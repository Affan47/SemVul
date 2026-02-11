hot_dynamic(struct clause *c)
{
  struct clause *hc;

  hc = cl_copy(c);
  hc->parents = copy_ilist(c->parents);
  hc->heat_level = c->heat_level;
  hot_cl_integrate(hc);

  if (!Hot->first_cl)
    init_hot();

  hot_index_clause(hc);
  append_cl(Hot, hc);
  Stats[HOT_SIZE]++;
  printf("\nHOT NEW CLAUSE!: "); print_clause(stdout, hc); printf("\n");

}
