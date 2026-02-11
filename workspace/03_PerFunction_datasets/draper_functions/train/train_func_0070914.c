lam_coll2pt(int cid)
{
  if (cid < 0)
    cid = FLIPCID(cid);
  return(cid);
}
