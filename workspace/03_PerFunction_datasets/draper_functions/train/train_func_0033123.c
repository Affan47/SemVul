get_ownertrust_with_min (PKT_public_key *pk)
{
  unsigned int otrust,otrust_min;

  otrust = (get_ownertrust (pk) & TRUST_MASK);
  otrust_min = get_min_ownertrust (pk);
  if(otrust<otrust_min)
    {


      otrust=otrust_min;
    }

  return otrust;
}
