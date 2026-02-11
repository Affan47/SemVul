gth_sa_alphastring(const GthSA *sa)
{
  gt_assert(sa);
  return gth_sa_alphatype(sa) == DNA_ALPHA ? "cDNA" : "Protein";
}
