gth_sa_acceptor_site_prob(const GthSA *sa, unsigned long intron)
{
  float prob;
  gt_assert(sa);
  prob = ((Introninfo*) gt_array_get(sa->introns, intron))
         ->acceptorsiteprobability;
  if (0.0005 > prob)
    return 0.0;
  return prob;
}
